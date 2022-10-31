/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 12:35:47
 * @FilePath: /hlibc/stack/stack.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_STACH_H__
#define __HLIBC_STACH_H__

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
typedef struct _stack_t* stack_ptr_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 创建一个 stack 容器
 * @return 返回新创建的 stack 容器
 */
extern stack_ptr_t stack_create(void);

/**
 * 删除给定的 stack 容器
 * @param stack 一个由 `stack_create` 返回的容器
 */
extern void stack_destroy(stack_ptr_t stack);

/*=====================
 * Setter functions
 *====================*/

extern status_t stack_push(stack_ptr_t stack, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data);
extern status_t stack_pop(stack_ptr_t stack);

/**
 * 清理 stack 容器的所有内容
 * @param stack 一个由 `stack_create` 返回的容器
 * ！！！慎用：调用此函数将会清理掉栈内容，对于普通数据而言并无影响；
 * 但是对于指针数据来说，一旦清空栈之后便无法找到其指针，除非使用者有其他记录。
 */
extern void stack_clear(stack_ptr_t stack);

/*=======================
 * Getter functions
 *======================*/

extern data_ptr_t stack_top(stack_ptr_t stack);
extern bool stack_empty(stack_ptr_t stack);
extern uint32_t stack_size(stack_ptr_t stack);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
