/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:41
 * @FilePath: /hlibc/list/list.c
 * @Description: None
 * @other: None
 */
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* 初始化列表 */
static status_t list_init(link_list_t *list)
{
    list->head = (list_node_t *) malloc(sizeof (list_node_t));
    if (list->head == NULL) return ERROR;
    list->head->data_ptr = NULL;
    list->head->next = NULL;
    list->size = 0;
    return OK;
}

link_list_t* list_create(void)
{
    link_list_t* list = (link_list_t *) malloc(sizeof (link_list_t));
    if (list != NULL) list_init(list);
    return list;
}

/*
 node : 插入新节点的位置（位于node节点之后）；
        如果node为NULL，则在表尾插入新节点
 data : 新节点的数据域
*/
status_t list_insert_with_node(link_list_t *list, list_node_t *node, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    list_node_t* pre;
    list_node_t* p = list->head;
    do {
        pre = p;
        p = p->next;
    } while (p != NULL && p != node);
    if (p != node) return ERROR;
    list_node_t *new_node = (list_node_t *) malloc(sizeof (list_node_t));
    new_node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL) copy_data(new_node->data_ptr, data_ptr);
    else                   memcpy(new_node->data_ptr, data_ptr, data_size);
    if (p == NULL) p = pre;
    new_node->next = p->next;
    p->next = new_node;
    ++list->size;
    return OK;
}

status_t list_insert_with_index(link_list_t *list, uint32_t index, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    list_node_t *p = list->head;
    if (index > list_get_size(list)+1) return ERROR;
    uint32_t i;
    for (i = 0; p != NULL && i < index - 1; ++i) p = p->next;
    if (p == NULL || i > index -1) return ERROR;
    list_node_t *new_node = (list_node_t *) malloc(sizeof (list_node_t));
    new_node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL) copy_data(new_node->data_ptr, data_ptr);
    else                   memcpy(new_node->data_ptr, data_ptr, data_size);
    new_node->next = p->next;
    p->next = new_node;
    ++list->size;
    return OK;
}

status_t list_append(link_list_t *list, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    return list_insert_with_node(list, NULL, data_ptr, data_size, copy_data);
}

list_node_t *list_get_node(link_list_t *list, uint32_t index)
{
    list_node_t *p = list->head->next;
    if (index > list_get_size(list)) return NULL;
    for (uint32_t i = 1; p != NULL && i < index; ++i) {
        p = p->next;
    }
    return p;
}

data_ptr_t list_get_data(link_list_t *list, uint32_t index)
{
    list_node_t *p = list_get_node(list, index);
    return p != NULL ? p->data_ptr : NULL;
}

status_t list_delete(link_list_t *list, list_node_t *node)
{
    list_node_t *p = list->head;
    while (p->next != NULL && p->next != node) p = p->next;
    if (p->next == NULL) return ERROR;
    list_node_t *q = p->next;
    p->next = q->next;
    free(q->data_ptr);
    free(q);
    --list->size;
    return OK;
}

void list_clear(link_list_t *list)
{
    list_node_t *p = list->head->next;
    while (p != NULL) {
        list_node_t* q = p;
        p = p->next;
        free(q->data_ptr);
        free(q);
    }
    list->head->next = NULL;
    list->size = 0;
}

void list_destroy(link_list_t *list)
{
    list_clear(list);
    free(list->head);
    free(list);
}

uint32_t list_get_size(link_list_t *list)
{
    return list->size;
}


/* ---------------------------------------------------------------------------- */
static list_dnode_t *create_new_node(const data_ptr_t data_ptr, uint32_t data_size);
static status_t insert(list_dnode_t* node, const data_ptr_t data_ptr, uint32_t data_size);
static void push_back(list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
static void push_front(list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
static data_ptr_t back(list_t *list);
static data_ptr_t front(list_t *list);
static uint32_t len(list_t *list);
static list_iterator_t begin(struct list_t *list);
static list_iterator_t end(struct list_t *list);
static void list_iterator_init(list_iterator_t *iterator, list_dnode_t* head, list_dnode_t* begin);

status_t dlist_init(list_t *list)
{
    list->head = (list_dnode_t *) malloc(sizeof (list_dnode_t));
    if (list->head == NULL) return ERROR;
    list->head->data_ptr = NULL;
    list->head->pre = list->head;
    list->head->next = list->head;
    list->size = 0;

    list->back = back;
    list->front = front;
    list->insert = insert;
    list->push_back = push_back;
    list->push_front = push_front;
    list->pop_back = NULL;
    list->pop_front = NULL;
    list->len = len;
    list->begin = begin;
    list->end = end;
    return OK;
}

static list_dnode_t *create_new_node(const data_ptr_t data_ptr, uint32_t data_size)
{
    list_dnode_t *node = (list_dnode_t *) malloc(sizeof (list_dnode_t));
    node->data_ptr = (data_ptr_t) malloc(data_size);
    memcpy(node->data_ptr, data_ptr, data_size);
    return node;
}

static status_t insert(list_dnode_t* where, const data_ptr_t data_ptr, uint32_t data_size)
{
    if(where == NULL) return ERROR;
    list_dnode_t *node = create_new_node(data_ptr, data_size);
    node->next = where->next;
    where->next->pre = node;
    node->pre = where;
    where->next = node;
    return OK;
}

static void push_back(list_t *list, const data_ptr_t data_ptr, uint32_t data_size)
{
    if (insert(list->head->pre, data_ptr, data_size) == OK)
        ++list->size;
}

static void push_front(list_t *list, const data_ptr_t data_ptr, uint32_t data_size)
{
    if (insert(list->head, data_ptr, data_size) == OK)
        ++list->size;
}

static data_ptr_t back(list_t *list)
{
    return list->head->pre->data_ptr;
}

static data_ptr_t front(list_t *list)
{
    return list->head->next->data_ptr;
}

static uint32_t len(list_t *list)
{
    return list->size;
}

static list_iterator_t begin(struct list_t *list)
{
    list_iterator_t it;
    list_iterator_init(&it, list->head, list->head->next);
    return it;
}

static list_iterator_t end(struct list_t *list)
{
    list_iterator_t it;
    list_iterator_init(&it, list->head, list->head->pre);
    return it;
}

static data_ptr_t data(list_iterator_t *iterator);
static void forward(list_iterator_t *iterator);
static void backward(list_iterator_t *iterator);

static void list_iterator_init(list_iterator_t *iterator, list_dnode_t* head, list_dnode_t* begin)
{
    iterator->begin = begin;
    iterator->end = NULL;
    iterator->head = head;
    iterator->data = data;
    iterator->forward = forward;
    iterator->backward = backward;
}

static data_ptr_t data(list_iterator_t *iterator)
{
    return iterator->begin != NULL ? iterator->begin->data_ptr : NULL;
}

static void forward(list_iterator_t *iterator)
{
    if (iterator->begin == NULL) return;
    iterator->begin = iterator->begin->next;
    if (iterator->begin == iterator->head) {
        iterator->end = iterator->begin->next;
        iterator->begin = iterator->end;
    }
}

static void backward(list_iterator_t *iterator)
{
    if (iterator->begin == NULL) return;
    iterator->begin = iterator->begin->pre;
    if (iterator->begin == iterator->head) {
        iterator->end = iterator->begin->pre;
        iterator->begin = iterator->end;
    }
}
