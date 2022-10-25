/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 12:35:41
 * @FilePath: /hlibc/stack/stack.c
 * @Description: None
 * @other: None
 */
#include <stdlib.h>
#include <string.h>
#include "stack.h"

link_stack* stack_create(void)
{
    link_stack* stack = (link_stack *) malloc(sizeof (link_stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

status_t stack_push(link_stack *stack, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    stack_node_t *node = (stack_node_t*) malloc(sizeof (stack_node_t));
    node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL) copy_data(node->data_ptr, data_ptr);
    else                   memcpy(node->data_ptr, data_ptr, data_size);
    node->next = stack->top;
    stack->top = node;
    ++stack->size;
    return OK;
}

status_t stack_pop(link_stack *stack)
{
    if(stack->top == NULL) return ERROR;
    stack_node_t *p = stack->top;
    stack->top = stack->top->next;
    free(p->data_ptr);
    free(p);
    --stack->size;
    return OK;
}

data_ptr_t stack_top(link_stack *stack)
{
    return stack->top->data_ptr;
}

bool stack_empty(link_stack *stack)
{
    return stack->size == 0 ? true : false;
}

void stack_clear(link_stack *stack)
{
    while (stack->size != 0) {
        stack_pop(stack);
    }
}

void stack_destroy(link_stack *stack)
{
    stack_clear(stack);
    free(stack);
}

uint32_t stack_get_size(link_stack *stack)
{
    return stack->size;
}
