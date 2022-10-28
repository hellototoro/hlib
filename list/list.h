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
    list_dnode_t *head;
    list_dnode_t *begin, *end;
    data_ptr_t (*data)(struct list_iterator_t *iterator);
    void (*forward)(struct list_iterator_t *iterator);
    void (*backward)(struct list_iterator_t *iterator);
    void (*forward_to)(struct list_iterator_t *iterator, int step);
    void (*backward_to)(struct list_iterator_t *iterator, int step);
} list_iterator_t;

typedef struct list_t{
    list_dnode_t head; /* 确保head的首地址与list的首地址重合 */
    data_ptr_t (*back)(struct list_t *list);
    data_ptr_t (*front)(struct list_t *list);
    bool (*empty)(struct list_t *list);
    void (*insert)(list_iterator_t* where, const data_ptr_t data_ptr, uint32_t data_size);
    void (*push_back)(struct list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
    void (*push_front)(struct list_t *list, const data_ptr_t data_ptr, uint32_t data_size);
    void (*pop_back)(struct list_t *list);
    void (*pop_front)(struct list_t *list);
    list_iterator_t (*begin)(struct list_t *list);
    list_iterator_t (*end)(struct list_t *list);
    uint32_t size;
} list_t;

extern status_t list_init(list_t *list);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
