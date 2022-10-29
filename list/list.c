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

static list_dnode_t *create_dnode(const data_ptr_t data_ptr, uint32_t data_size);
static data_ptr_t back(list_t *list);
static data_ptr_t front(list_t *list);
static bool empty(list_t *list);
static void insert(list_iterator_t* node, const data_ptr_t data_ptr, uint32_t data_size);
static void push_back(list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
static void push_front(list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
static void pop_back(list_t *list);
static void pop_front(list_t *list);
static list_iterator_t begin(list_t *list);
static list_iterator_t end(list_t *list);
static status_t _insert(list_t *list, list_dnode_t *where, const data_ptr_t data_ptr, uint32_t data_size);
static void _delete(list_t *list, list_dnode_t *where);

/* 迭代器 */
static void list_iterator_init(list_iterator_t *iterator, list_dnode_t* head, list_dnode_t* begin);
static data_ptr_t data(list_iterator_t *iterator);
static void forward(list_iterator_t *iterator);
static void backward(list_iterator_t *iterator);
static void forward_to(list_iterator_t *iterator, int step);
static void backward_to(list_iterator_t *iterator, int step);

status_t list_init(list_t *list)
{
    list->head.data_ptr = NULL;
    list->head.prev = &list->head;
    list->head.next = &list->head;
    list->size = 0;

    list->back = back;
    list->front = front;
    list->empty = empty;
    list->insert = insert;
    list->push_back = push_back;
    list->push_front = push_front;
    list->pop_back = pop_back;
    list->pop_front = pop_front;
    list->begin = begin;
    list->end = end;
    return OK;
}

static list_dnode_t *create_dnode(const data_ptr_t data_ptr, uint32_t data_size)
{
    list_dnode_t *node = (list_dnode_t *) malloc(sizeof (list_dnode_t));
    if (node == NULL) return NULL;
    node->data_ptr = (data_ptr_t) malloc(data_size);
    memcpy(node->data_ptr, data_ptr, data_size);
    return node;
}

static data_ptr_t back(list_t *list)
{
    return list->head.prev->data_ptr;
}

static data_ptr_t front(list_t *list)
{
    return list->head.next->data_ptr;
}

static bool empty(list_t *list)
{
    return list->head.prev == list->head.next ? true : false;
}

static status_t _insert(list_t *list, list_dnode_t *where, const data_ptr_t data_ptr, uint32_t data_size)
{
    list_dnode_t *node = create_dnode(data_ptr, data_size);
    if (node == NULL) return ERROR;
    node->next = where->next;
    where->next->prev = node;
    node->prev = where;
    where->next = node;
    ++list->size;
    return OK;
}

static void _delete(list_t *list, list_dnode_t *where)
{
    if (empty(list)) return;
    where->prev->next = where->next;
    where->next->prev = where->prev;
    free(where->data_ptr);
    free(where);
    --list->size;
}

static void insert(list_iterator_t* where, const data_ptr_t data_ptr, uint32_t data_size)
{
    list_t *list = (list_t *)where->head;
    _insert(list, where->begin->prev, data_ptr, data_size);
}

static void push_back(list_t *list, const data_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, list->head.prev, data_ptr, data_size);
}

static void push_front(list_t *list, const data_ptr_t data_ptr, uint32_t data_size)
{
    _insert(list, list->head.next, data_ptr, data_size);
}

static void pop_back(list_t *list)
{
    _delete(list, list->head.prev);
}

static void pop_front(list_t *list)
{
    _delete(list, list->head.next);
}

static list_iterator_t begin(struct list_t *list)
{
    list_iterator_t it;
    list_iterator_init(&it, &list->head, list->head.next);
    return it;
}

static list_iterator_t end(struct list_t *list)
{
    list_iterator_t it;
    list_iterator_init(&it, &list->head, list->head.prev);
    return it;
}

static void list_iterator_init(list_iterator_t *iterator, list_dnode_t* head, list_dnode_t* begin)
{
    iterator->begin = begin;
    iterator->end = NULL;
    iterator->head = head;
    iterator->data = data;
    iterator->forward = forward;
    iterator->backward = backward;
    iterator->forward_to = forward_to;
    iterator->backward_to = backward_to;
}

static data_ptr_t data(list_iterator_t *iterator)
{
    return iterator->begin != iterator->head ? iterator->begin->data_ptr : NULL;
}

static void forward(list_iterator_t *iterator)
{
    iterator->begin = iterator->begin->next;
    if (iterator->begin == iterator->head) {
        iterator->end = iterator->begin->next;
        iterator->begin = iterator->end;
    }
}

static void forward_to(list_iterator_t *iterator, int step)
{
    while(step) {
        forward(iterator);
        --step;
    }
}

static void backward(list_iterator_t *iterator)
{
    iterator->begin = iterator->begin->prev;
    if (iterator->begin == iterator->head) {
        iterator->end = iterator->begin->prev;
        iterator->begin = iterator->end;
    }
}

static void backward_to(list_iterator_t *iterator, int step)
{
    while(step) {
        backward(iterator);
        --step;
    }
}
