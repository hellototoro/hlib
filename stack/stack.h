/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 12:35:47
 * @FilePath: /hlibc/stack/stack.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_STACH_H__
#define __HLIBC_STACH_H__

#include "../common/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef node_t stack_node_t;

typedef struct {
    uint32_t size;
    stack_node_t* top;
} link_stack_t;

extern link_stack_t* stack_create(void);
extern status_t stack_push(link_stack_t *stack, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data);
extern status_t stack_pop(link_stack_t *stack);
extern data_ptr_t stack_top(link_stack_t *stack);
extern bool stack_empty(link_stack_t *stack);
/* ！！！慎用：调用此函数将会清理掉栈内容，对于普通数据而言并无影响；
 * 但是对于指针数据来说，一旦清空栈之后便无法找到其指针，除非使用者有其他记录*/
extern void stack_clear(link_stack_t *stack);
extern void stack_destroy(link_stack_t *stack);
extern uint32_t stack_get_size(link_stack_t *stack);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
