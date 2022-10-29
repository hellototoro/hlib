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
static data_ptr_t back(list_t *self);
static data_ptr_t front(list_t *self);
static bool empty(list_t *self);
static void insert(list_iterator_t* node, const data_ptr_t data_ptr, uint32_t data_size);
static void push_back(list_t *self, const data_ptr_t data_ptr, uint32_t data_size);
static void push_front(list_t *self, const data_ptr_t data_ptr, uint32_t data_size);
static void pop_back(list_t *self);
static void pop_front(list_t *self);
static list_iterator_t begin(list_t *self);
static list_iterator_t end(list_t *self);
static status_t _insert(list_t *self, list_dnode_t *where, const data_ptr_t data_ptr, uint32_t data_size);
static void _delete(list_t *self, list_dnode_t *where);

/* 迭代器 */
static void list_iterator_init(list_iterator_t *iter, list_dnode_t* head, list_dnode_t* pointer);
static data_ptr_t data(list_iterator_t *self);
static void forward(list_iterator_t *self);
static void backward(list_iterator_t *self);
static void forward_to(list_iterator_t *self, int step);
static void backward_to(list_iterator_t *self, int step);
static bool is_end(list_iterator_t *self);

status_t list_init(list_t *list, uint32_t type_size)
{
    list->head.data_ptr = (data_ptr_t) malloc(type_size); /* 为 head 节点分配空间：当 list 为空的时候，确保正常访问 */
    memset(list->head.data_ptr, '\0', type_size); /* 使用 '\0' 是为了兼容字符串类型的数据 */
    list->head.prev = &list->tail;
    list->head.next = &list->tail;
    list->tail.data_ptr = list->head.data_ptr;
    list->tail.prev = &list->head;
    list->tail.next = &list->head;
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
    if (node->data_ptr == NULL) {
        free(node);
        return NULL;
    }
    memcpy(node->data_ptr, data_ptr, data_size);
    return node;
}

static data_ptr_t back(list_t *self)
{
    return self->tail.prev->data_ptr;
}

static data_ptr_t front(list_t *self)
{
    return self->head.next->data_ptr;
}

static bool empty(list_t *self)
{
    return self->head.data_ptr == self->tail.data_ptr ? true : false;
}

static status_t _insert(list_t *self, list_dnode_t *where, const data_ptr_t data_ptr, uint32_t data_size)
{
    list_dnode_t *node = create_dnode(data_ptr, data_size);
    if (node == NULL) return ERROR;
    node->next = where->next;
    where->next->prev = node;
    node->prev = where;
    where->next = node;
    if (node->next == &self->tail)
        self->tail.data_ptr = node->data_ptr;
    ++self->size;
    return OK;
}

static void _delete(list_t *self, list_dnode_t *where)
{
    if (empty(self)) return;
    if (where->next == &self->tail)
        self->tail.data_ptr = where->prev->data_ptr;
    where->prev->next = where->next;
    where->next->prev = where->prev;
    free(where->data_ptr);
    free(where);
    --self->size;
}

static void insert(list_iterator_t* where, const data_ptr_t data_ptr, uint32_t data_size)
{
    list_t *list = (list_t *)where->head;
    _insert(list, where->pointer->prev, data_ptr, data_size);
}

static void push_back(list_t *self, const data_ptr_t data_ptr, uint32_t data_size)
{
    _insert(self, self->tail.prev, data_ptr, data_size);
}

static void push_front(list_t *self, const data_ptr_t data_ptr, uint32_t data_size)
{
    _insert(self, self->head.next, data_ptr, data_size);
}

static void pop_back(list_t *self)
{
    _delete(self, self->tail.prev);
}

static void pop_front(list_t *self)
{
    _delete(self, self->head.next);
}

static list_iterator_t begin(struct list_t *self)
{
    list_iterator_t it;
    list_iterator_init(&it, &self->head, self->head.next);
    return it;
}

static list_iterator_t end(struct list_t *self)
{
    list_iterator_t it;
    list_iterator_init(&it, &self->head, &self->tail);
    return it;
}

static void list_iterator_init(list_iterator_t *iter, list_dnode_t* head, list_dnode_t* pointer)
{
    iter->head = head;
    iter->tail = head->prev;
    iter->pointer = pointer;
    iter->data = data;
    iter->forward = forward;
    iter->backward = backward;
    iter->forward_to = forward_to;
    iter->backward_to = backward_to;
    iter->is_end = is_end;
}

static data_ptr_t data(list_iterator_t *self)
{
    return self->pointer->data_ptr;
}

static void forward(list_iterator_t *self)
{
    self->pointer = self->pointer->next;
    if (self->pointer == self->head)
        self->pointer = self->pointer->next;
}

static void forward_to(list_iterator_t *self, int step)
{
    while(step) {
        forward(self);
        --step;
    }
}

static void backward(list_iterator_t *self)
{
    self->pointer = self->pointer->prev;
    if (self->pointer == self->head)
        self->pointer = self->pointer->prev;
}

static void backward_to(list_iterator_t *self, int step)
{
    while(step) {
        backward(self);
        --step;
    }
}

static bool is_end(list_iterator_t *self)
{
    return self->pointer == self->tail ? true : false;
}
