/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 32:37:34
 * @FilePath: /hlibc/queue/queue.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_QUEUE_H__
#define __HLIBC_QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../common/common.h"

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _queue_t* queue_ptr_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**
 * 创建一个 queue 容器
 * @return 返回新创建的 queue 容器
 */
extern queue_ptr_t queue_create(void);

/**
 * 删除给定的 queue 容器
 * @param queue 一个由 `queue_create` 返回的容器
 */
extern void queue_destroy(queue_ptr_t queue);

/*=====================
 * Setter functions
 *====================*/

extern status_t queue_push(queue_ptr_t queue, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data);
extern status_t queue_pop(queue_ptr_t queue);

/**
 * 清理 queue 容器的所有内容
 * @param queue 一个由 `queue_create` 返回的容器
 * ！！！慎用：调用此函数将会清理掉队列内容，对于普通数据而言并无影响；
 * 但是对于指针数据来说，一旦清空栈之后便无法找到其指针，除非使用者有其他记录。
 */
extern void queue_clear(queue_ptr_t queue);

/*=======================
 * Getter functions
 *======================*/

extern data_ptr_t queue_front(queue_ptr_t queue);
extern data_ptr_t queue_rear(queue_ptr_t queue);
extern bool queue_empty(queue_ptr_t queue);
extern uint32_t queue_size(queue_ptr_t queue);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
