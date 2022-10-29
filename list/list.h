/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:54
 * @FilePath: /hlibc/list/list.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_LIST_H__
#define __HLIBC_LIST_H__

#include "../common/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef dnode_t list_dnode_t;

typedef struct list_iterator_t{
    list_dnode_t *head, *tail;
    list_dnode_t *pointer;
    data_ptr_t (*data)(struct list_iterator_t *self);
    void (*forward)(struct list_iterator_t *self);
    void (*backward)(struct list_iterator_t *self);
    void (*forward_to)(struct list_iterator_t *self, int step);
    void (*backward_to)(struct list_iterator_t *self, int step);
    bool (*is_end)(struct list_iterator_t *self);
} list_iterator_t;

typedef struct list_t{
    list_dnode_t head; /* 确保head的首地址与list的首地址重合 */
    list_dnode_t tail;
    data_ptr_t (*back)(struct list_t *self);
    data_ptr_t (*front)(struct list_t *self);
    bool (*empty)(struct list_t *self);
    void (*insert)(list_iterator_t* where, const data_ptr_t data_ptr, uint32_t data_size);
    void (*push_back)(struct list_t *self, const data_ptr_t data_ptr, uint32_t data_size);
    void (*push_front)(struct list_t *self, const data_ptr_t data_ptr, uint32_t data_size);
    void (*pop_back)(struct list_t *self);
    void (*pop_front)(struct list_t *self);
    list_iterator_t (*begin)(struct list_t *self);
    list_iterator_t (*end)(struct list_t *self);
    uint32_t size;
} list_t;

extern status_t list_init(list_t *list, uint32_t type_size);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
