/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 12:35:41
 * @FilePath: /hlibc/stack/stack.c
 * @Description: None
 * @other: None
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "../common/hlibc_type.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct node stack_node_t;
struct _stack_t{
    uint32_t size;
    stack_node_t* top;
    data_ptr_t empty_data_ptr; /* 当 stack 为空时， top 节点的数据指针指向 empty_data */
};

/**********************
 *   GLOBAL VARIABLES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

stack_ptr_t stack_create(uint32_t type_size)
{
    stack_ptr_t stack = (stack_ptr_t) malloc(sizeof (struct _stack_t));
    stack->empty_data_ptr = (data_ptr_t) malloc(type_size); /* 当 stack 为空的时候，确保正常访问 */
    memset(stack->empty_data_ptr, '\0', type_size); /* 使用 '\0' 是为了兼容字符串类型的数据 */
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void stack_destroy(stack_ptr_t stack)
{
    stack_clear(stack);
    free(stack->empty_data_ptr);
    free(stack);
}

/*=====================
 * Setter functions
 *====================*/

status_t stack_push(stack_ptr_t stack, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    stack_node_t *node = (stack_node_t*) malloc(sizeof (stack_node_t));
    node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL)
        copy_data(node->data_ptr, data_ptr);
    else
        memcpy(node->data_ptr, data_ptr, data_size);
    node->next = stack->top;
    stack->top = node;
    ++stack->size;
    return OK;
}

status_t stack_pop(stack_ptr_t stack)
{
    if(stack->top == NULL) return ERROR;
    stack_node_t *p = stack->top;
    stack->top = stack->top->next;
    free(p->data_ptr);
    free(p);
    --stack->size;
    return OK;
}

void stack_clear(stack_ptr_t stack)
{
    while (!stack_empty(stack)) {
        stack_pop(stack);
    }
}

/*=======================
 * Getter functions
 *======================*/

data_ptr_t stack_top(stack_ptr_t stack)
{
    return !stack_empty(stack) ? stack->top->data_ptr : stack->empty_data_ptr;
}

bool stack_empty(stack_ptr_t stack)
{
    return stack->size == 0 ? true : false;
}

uint32_t stack_size(stack_ptr_t stack)
{
    return stack->size;
}
