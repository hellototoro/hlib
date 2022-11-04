/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:41
 * @FilePath: /hlibc/list/list.c
 * @Description: None
 * @other: None
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "../common/hlibc_type.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct dnode list_dnode_t;
struct _list_t {
    uint32_t size;
    list_dnode_t head;
    data_ptr_t empty_data_ptr; /* 当链表为空时， head 节点的数据指针指向 empty_data */
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
static list_dnode_t *create_dnode(const data_ptr_t data_ptr, uint32_t data_size);
static status_t _insert(list_ptr_t list, list_dnode_t* position, const data_ptr_t data_ptr, uint32_t data_size);
static void _delete(list_ptr_t list, list_dnode_t* position);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
list_ptr_t list_create(uint32_t type_size)
{
    list_ptr_t list = (list_ptr_t)malloc(sizeof(struct _list_t));
    list->empty_data_ptr = (data_ptr_t) malloc(type_size); /* 为 head 节点分配空间：当 list 为空的时候，确保正常访问 */
    memset(list->empty_data_ptr, '\0', type_size); /* 使用 '\0' 是为了兼容字符串类型的数据 */
    list->head.data_ptr = list->empty_data_ptr;
    list->head.prev = &list->head;
    list->head.next = &list->head;
    list->size = 0;
    return list;
}

void list_destroy(list_ptr_t list)
{
    free(list->empty_data_ptr);
    free(list);
}

/*=====================
 * Setter functions
 *====================*/

void list_insert(list_ptr_t list, list_iterator_ptr_t position, const data_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, position->prev, data_ptr, data_size);
}

void list_push_back(list_ptr_t list, const data_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, list->head.prev, data_ptr, data_size);
}

void list_push_front(list_ptr_t list, const data_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, list->head.next, data_ptr, data_size);
}

void list_pop_back(list_ptr_t list)
{
    _delete(list, list->head.prev);
}

void list_pop_front(list_ptr_t list)
{
    _delete(list, list->head.next);
}

void list_clear(list_ptr_t list)
{
    while(!list_empty(list)) {
        _delete(list, list->head.next);
    }
}

/*=======================
 * Getter functions
 *======================*/

data_ptr_t list_back(list_ptr_t list)
{
    return list->head.prev->data_ptr;
}

data_ptr_t list_front(list_ptr_t list)
{
    return list->head.next->data_ptr;
}

list_iterator_ptr_t list_begin(list_ptr_t list)
{
    return list->head.next;
}

list_iterator_ptr_t list_end(list_ptr_t list)
{
    return &list->head;
}

bool list_empty(list_ptr_t list)
{
    return list->head.next == list->head.prev ? true : false;
}

uint32_t list_size(list_ptr_t list)
{
    return list->size;
}

/*=======================
 * Other functions
 *======================*/

/* 迭代器 */
data_ptr_t list_iter_data(list_iterator_ptr_t iter)
{
    return iter->data_ptr;
}

void list_iter_forward(list_iterator_ptr_t *iter)
{
    *iter = (*iter)->next;
}

void list_iter_forward_to(list_iterator_ptr_t *iter, int step)
{
    while(step) {
        list_iter_forward(iter);
        --step;
    }
}

void list_iter_backward(list_iterator_ptr_t *iter)
{
    *iter = (*iter)->prev;
}

void list_iter_backward_to(list_iterator_ptr_t *iter, int step)
{
    while(step) {
        list_iter_backward(iter);
        --step;
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static list_dnode_t *create_dnode(const data_ptr_t data_ptr, uint32_t data_size)
{
    list_dnode_t *node = (list_dnode_t *) malloc(sizeof (list_dnode_t));
    if (node == NULL) return NULL;
    node->data_ptr = (data_ptr_t) malloc(data_size);
    if (node->data_ptr == NULL) {
        free(node);
        return NULL;
    }
    memcpy(node->data_ptr, data_ptr, data_size);
    return node;
}

static status_t _insert(list_ptr_t list, list_dnode_t* position, const data_ptr_t data_ptr, uint32_t data_size)
{
    list_dnode_t *node = create_dnode(data_ptr, data_size);
    if (node == NULL) return ERROR;
    node->next = position->next;
    position->next->prev = node;
    node->prev = position;
    position->next = node;
    if (node->next == &list->head)
        list->head.data_ptr = node->data_ptr;
    ++list->size;
    return OK;
}

static void _delete(list_ptr_t list, list_dnode_t* position)
{
    if (list_empty(list)) return;
    if (position->next == &list->head) {
        if (list->head.data_ptr != position->prev->data_ptr)
            list->head.data_ptr == position->prev->data_ptr;
        else /* 只有一个节点的情况 */
            list->head.data_ptr = list->empty_data_ptr;
    }
    position->prev->next = position->next;
    position->next->prev = position->prev;
    free(position->data_ptr);
    free(position);
    --list->size;
}
