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
static status_t insert(list_t *list, list_iterator_t* node, const data_ptr_t data_ptr, uint32_t data_size);
static void push_back(list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
static void push_front(list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
static void pop_back(struct list_t *list);
static void pop_front(struct list_t *list);
static list_iterator_t begin(struct list_t *list);
static list_iterator_t end(struct list_t *list);

/* 迭代器*/
static void list_iterator_init(list_iterator_t *iterator, list_dnode_t* head, list_dnode_t* begin);
static data_ptr_t data(list_iterator_t *iterator);
static void forward(list_iterator_t *iterator);
static void backward(list_iterator_t *iterator);

status_t list_init(list_t *list)
{
    list->head.data_ptr = NULL;
    list->head.pre = &list->head;
    list->head.next = &list->head;
    list->size = 0;

    list->back = back;
    list->front = front;
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
    node->data_ptr = (data_ptr_t) malloc(data_size);
    memcpy(node->data_ptr, data_ptr, data_size);
    return node;
}

static data_ptr_t back(list_t *list)
{
    return list->head.pre->data_ptr;
}

static data_ptr_t front(list_t *list)
{
    return list->head.next->data_ptr;
}

static status_t insert(list_t *list, list_iterator_t* where, const data_ptr_t data_ptr, uint32_t data_size)
{
    if(where == NULL) return ERROR;
    list_dnode_t *node = create_dnode(data_ptr, data_size);
    list_dnode_t *p = where->begin;
    node->next = p->next;
    p->next->pre = node;
    node->pre = p;
    p->next = node;
    ++list->size;
    return OK;
}

static void push_back(list_t *list, const data_ptr_t data_ptr, uint32_t data_size)
{
    list_iterator_t it = list->end(list);
    insert(list, &it, data_ptr, data_size);
}

static void push_front(list_t *list, const data_ptr_t data_ptr, uint32_t data_size)
{
    list_iterator_t it = list->begin(list); 
    insert(list, &it, data_ptr, data_size);
}

static void pop_back(struct list_t *list)
{
    list_dnode_t *p = list->head.pre;
    if (p == &list->head) return;
    list->head.pre = p->pre;
    p->pre->next = &list->head;
    free(p->data_ptr);
    free(p);
    --list->size;
}

static void pop_front(struct list_t *list)
{
    list_dnode_t *p = list->head.next;
    if (p == &list->head) return;
    list->head.next = p->next;
    p->next->pre = &list->head;
    free(p->data_ptr);
    free(p);
    --list->size;
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
    list_iterator_init(&it, &list->head, list->head.pre);
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
