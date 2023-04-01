/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:41
 * @FilePath: /hlibc/list/hlist.c
 * @Description: None
 * @other: None
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <string.h>
#include "hlist.h"
#include "../common/hlibc_type.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct hdnode list_dnode_t;
struct hlist {
    uint32_t list_size;
    uint32_t type_size;
    list_dnode_t head;
    hdata_ptr_t empty_data_ptr; /* 当链表为空时， head 节点的数据指针指向 empty_data */
};

/**********************
 *   GLOBAL VARIABLES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static list_dnode_t *create_dnode(const hdata_ptr_t data_ptr, uint32_t data_size);
static hlib_status_t _insert(hlist_ptr_t list, list_dnode_t* position, const hdata_ptr_t data_ptr, uint32_t data_size);
static void _delete(hlist_ptr_t list, list_dnode_t* position);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
hlist_ptr_t hlist_create(uint32_t type_size)
{
    hlist_ptr_t list = (hlist_ptr_t)malloc(sizeof(struct hlist));
    list->empty_data_ptr = (hdata_ptr_t) malloc(type_size); /* 为 head 节点分配空间：当 list 为空的时候，确保正常访问 */
    memset(list->empty_data_ptr, '\0', type_size); /* 使用 '\0' 是为了兼容字符串类型的数据 */
    list->head.data_ptr = list->empty_data_ptr;
    list->head.prev = &list->head;
    list->head.next = &list->head;
    list->list_size = 0;
    list->type_size = type_size;
    return list;
}

void hlist_destroy(hlist_ptr_t list)
{
    hlist_clear(list);
    free(list->empty_data_ptr);
    free(list);
}

/*=====================
 * Setter functions
 *====================*/

void hlist_insert(hlist_ptr_t list, hlist_iterator_ptr_t position, const hdata_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, position->prev, data_ptr, data_size);
}

void hlist_push_back(hlist_ptr_t list, const hdata_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, list->head.prev, data_ptr, data_size);
}

void hlist_push_front(hlist_ptr_t list, const hdata_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, list->head.next, data_ptr, data_size);
}

void hlist_pop_back(hlist_ptr_t list)
{
    _delete(list, list->head.prev);
}

void hlist_pop_front(hlist_ptr_t list)
{
    _delete(list, list->head.next);
}

void hlist_clear(hlist_ptr_t list)
{
    while(!hlist_empty(list)) {
        _delete(list, list->head.next);
    }
}

/*=======================
 * Getter functions
 *======================*/

hdata_ptr_t hlist_back(hlist_ptr_t list)
{
    return list->head.prev->data_ptr;
}

hdata_ptr_t hlist_front(hlist_ptr_t list)
{
    return list->head.next->data_ptr;
}

hlist_iterator_ptr_t hlist_begin(hlist_ptr_t list)
{
    return list->head.next;
}

hlist_iterator_ptr_t hlist_end(hlist_ptr_t list)
{
    return &list->head;
}

bool hlist_empty(hlist_ptr_t list)
{
    return (list->list_size == 0);
}

uint32_t list_size(hlist_ptr_t list)
{
    return list->list_size;
}

/*=======================
 * Other functions
 *======================*/

/* 迭代器 */
hdata_ptr_t hlist_iter_data(hlist_iterator_ptr_t iter)
{
    return iter->data_ptr;
}

void hlist_iter_forward(hlist_iterator_ptr_t *iter)
{
    *iter = (*iter)->next;
}

void hlist_iter_forward_to(hlist_iterator_ptr_t *iter, int step)
{
    while(step) {
        hlist_iter_forward(iter);
        --step;
    }
}

void hlist_iter_backward(hlist_iterator_ptr_t *iter)
{
    *iter = (*iter)->prev;
}

void hlist_iter_backward_to(hlist_iterator_ptr_t *iter, int step)
{
    while(step) {
        hlist_iter_backward(iter);
        --step;
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static list_dnode_t *create_dnode(const hdata_ptr_t data_ptr, uint32_t data_size)
{
    list_dnode_t *node = (list_dnode_t *) malloc(sizeof (list_dnode_t));
    if (node == NULL) return NULL;
    node->data_ptr = (hdata_ptr_t) malloc(data_size);
    if (node->data_ptr == NULL) {
        free(node);
        return NULL;
    }
    memcpy(node->data_ptr, data_ptr, data_size);
    return node;
}

static hlib_status_t _insert(hlist_ptr_t list, list_dnode_t* position, const hdata_ptr_t data_ptr, uint32_t data_size)
{
    if(data_size != list->type_size) return HLIB_ERROR;
    list_dnode_t *node = create_dnode(data_ptr, data_size);
    if (node == NULL) return HLIB_ERROR;
    node->next = position->next;
    position->next->prev = node;
    node->prev = position;
    position->next = node;
    if (node->next == &list->head)
        list->head.data_ptr = node->data_ptr;
    ++list->list_size;
    return HLIB_OK;
}

static void _delete(hlist_ptr_t list, list_dnode_t* position)
{
    if (hlist_empty(list)) return;
    if (position->next == &list->head) {
        if (list->head.data_ptr != position->prev->data_ptr)
            list->head.data_ptr = position->prev->data_ptr;
        else /* 只有一个节点的情况 */
            list->head.data_ptr = list->empty_data_ptr;
    }
    position->prev->next = position->next;
    position->next->prev = position->prev;
    free(position->data_ptr);
    free(position);
    --list->list_size;
}
