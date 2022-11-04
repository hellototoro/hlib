/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:54
 * @FilePath: /hlibc/list/list.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_LIST_H__
#define __HLIBC_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../common/common.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _list_t* list_ptr_t;
typedef struct dnode* list_iterator_ptr_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 创建一个 list 容器
 * @param type_size 装入容器的数据类型的大小。例：`list_create(sizeof(int));`
 * @return 返回新创建的容器
 */
extern list_ptr_t list_create(uint32_t type_size);

/**
 * 删除给定的 list 容器
 * @param list 一个由 `list_create` 返回的容器
 */
extern void list_destroy(list_ptr_t list);

/*=====================
 * Setter functions
 *====================*/

extern void list_insert(list_ptr_t list, list_iterator_ptr_t position, const data_ptr_t data_ptr, uint32_t data_size);
extern void list_push_back(list_ptr_t list, const data_ptr_t data_ptr, uint32_t data_size);
extern void list_push_front(list_ptr_t list, const data_ptr_t data_ptr, uint32_t data_size);
extern void list_pop_back(list_ptr_t list);
extern void list_pop_front(list_ptr_t list);
extern void list_clear(list_ptr_t list);

/*=======================
 * Getter functions
 *======================*/

extern data_ptr_t list_back(list_ptr_t list);
extern data_ptr_t list_front(list_ptr_t list);
extern list_iterator_ptr_t list_begin(list_ptr_t list);
extern list_iterator_ptr_t list_end(list_ptr_t list);
extern bool list_empty(list_ptr_t list);
extern uint32_t list_size(list_ptr_t list);

/*=======================
 * Other functions
 *======================*/

/* 迭代器 */
extern data_ptr_t list_iter_data(list_iterator_ptr_t iter);
extern void list_iter_forward(list_iterator_ptr_t *iter);
extern void list_iter_backward(list_iterator_ptr_t *iter);
extern void list_iter_forward_to(list_iterator_ptr_t *iter, int step);
extern void list_iter_backward_to(list_iterator_ptr_t *iter, int step);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
