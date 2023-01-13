/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:54
 * @FilePath: /hlibc/list/hlist.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_HLIST_H__
#define __HLIBC_HLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../common/hcommon.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct hlist* hlist_ptr_t;
typedef struct hdnode* hlist_iterator_ptr_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 创建一个 list 容器
 * @param type_size 装入容器的数据类型的大小。例：`hlist_create(sizeof(int));`
 * @return 返回新创建的容器
 */
extern hlist_ptr_t hlist_create(uint32_t type_size);

/**
 * 删除给定的 list 容器
 * @param list 一个由 `hlist_create` 返回的容器
 */
extern void hlist_destroy(hlist_ptr_t list);

/*=====================
 * Setter functions
 *====================*/

extern void hlist_insert(hlist_ptr_t list, hlist_iterator_ptr_t position, const hdata_ptr_t data_ptr, uint32_t data_size);
extern void hlist_push_back(hlist_ptr_t list, const hdata_ptr_t data_ptr, uint32_t data_size);
extern void hlist_push_front(hlist_ptr_t list, const hdata_ptr_t data_ptr, uint32_t data_size);
extern void hlist_pop_back(hlist_ptr_t list);
extern void hlist_pop_front(hlist_ptr_t list);
extern void hlist_clear(hlist_ptr_t list);

/*=======================
 * Getter functions
 *======================*/

extern hdata_ptr_t hlist_back(hlist_ptr_t list);
extern hdata_ptr_t hlist_front(hlist_ptr_t list);
extern hlist_iterator_ptr_t hlist_begin(hlist_ptr_t list);
extern hlist_iterator_ptr_t hlist_end(hlist_ptr_t list);
extern bool hlist_empty(hlist_ptr_t list);
extern uint32_t list_size(hlist_ptr_t list);

/*=======================
 * Other functions
 *======================*/

/* 迭代器 */
extern hdata_ptr_t hlist_iter_data(hlist_iterator_ptr_t iter);
extern void hlist_iter_forward(hlist_iterator_ptr_t *iter);
extern void hlist_iter_backward(hlist_iterator_ptr_t *iter);
extern void hlist_iter_forward_to(hlist_iterator_ptr_t *iter, int step);
extern void hlist_iter_backward_to(hlist_iterator_ptr_t *iter, int step);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
