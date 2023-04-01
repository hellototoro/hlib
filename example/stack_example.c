/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 18:48:08
 * @FilePath: /hlibc/example/stack_example.c
 * @Description: None
 * @other: None
 */
#include <stdio.h>
#include "../src/stack/hstack.h"

// static void copy_data(void* dest, const void* src)
// {
//     int* d =  (int*)dest;
//     const int* s = (int*)src;
//     *d = *s;
// }

void stack_example1(void)
{
    hstack_ptr_t stack = hstack_create(sizeof(int));
    int a = 10;
    hstack_push(stack, &a, sizeof(a), NULL);
    a = 20;
    hstack_push(stack, &a, sizeof(a), NULL);
    a = 30;
    hstack_push(stack, &a, sizeof(a), NULL);
    int size = hstack_size(stack);
    for (int i = 0; i < size; ++i) {
        int x = DATA_CAST(int)hstack_top(stack);
        hstack_pop(stack);
        printf("%d ", x);
    }
    hstack_destroy(stack);
    printf("\n");
}
