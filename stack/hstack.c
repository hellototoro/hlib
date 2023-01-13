/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 12:35:41
 * @FilePath: /hlibc/stack/hstack.c
 * @Description: None
 * @other: None
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <string.h>
#include "hstack.h"
#include "../common/hlibc_type.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct hnode hstack_node_t;
struct hstack{
    uint32_t size;
    hstack_node_t* top;
    hdata_ptr_t empty_data_ptr; /* 当 stack 为空时， top 节点的数据指针指向 empty_data */
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

hstack_ptr_t hstack_create(uint32_t type_size)
{
    hstack_ptr_t stack = (hstack_ptr_t) malloc(sizeof (struct hstack));
    stack->empty_data_ptr = (hdata_ptr_t) malloc(type_size); /* 当 stack 为空的时候，确保正常访问 */
    memset(stack->empty_data_ptr, '\0', type_size); /* 使用 '\0' 是为了兼容字符串类型的数据 */
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void hstack_destroy(hstack_ptr_t stack)
{
    hstack_clear(stack);
    free(stack->empty_data_ptr);
    free(stack);
}

/*=====================
 * Setter functions
 *====================*/

hlib_status_t hstack_push(hstack_ptr_t stack, hdata_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    hstack_node_t *node = (hstack_node_t*) malloc(sizeof (hstack_node_t));
    node->data_ptr = (hdata_ptr_t) malloc(data_size);
    if (copy_data != NULL)
        copy_data(node->data_ptr, data_ptr);
    else
        memcpy(node->data_ptr, data_ptr, data_size);
    node->next = stack->top;
    stack->top = node;
    ++stack->size;
    return HLIB_OK;
}

hlib_status_t hstack_pop(hstack_ptr_t stack)
{
    if(stack->top == NULL) return HLIB_ERROR;
    hstack_node_t *p = stack->top;
    stack->top = stack->top->next;
    free(p->data_ptr);
    free(p);
    --stack->size;
    return HLIB_OK;
}

void hstack_clear(hstack_ptr_t stack)
{
    while (!hstack_empty(stack)) {
        hstack_pop(stack);
    }
}

/*=======================
 * Getter functions
 *======================*/

hdata_ptr_t hstack_top(hstack_ptr_t stack)
{
    return !hstack_empty(stack) ? stack->top->data_ptr : stack->empty_data_ptr;
}

bool hstack_empty(hstack_ptr_t stack)
{
    return stack->size == 0 ? true : false;
}

uint32_t hstack_size(hstack_ptr_t stack)
{
    return stack->size;
}
