/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 18:48:08
 * @FilePath: /hlibc/example/stack_example.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "../stack/hstack.h"

void stack_example1(void)
{
    hstack_ptr_t stack = hstack_create(sizeof(int));
    int a = 10;
    hstack_push(stack, &a, sizeof(a), nullptr);
    a = 20;
    hstack_push(stack, &a, sizeof(a), nullptr);
    a = 30;
    hstack_push(stack, &a, sizeof(a), nullptr);
    int size = hstack_size(stack);
    for (auto i = 0; i < size; ++i) {
        int x = DATA_CAST(int)hstack_top(stack);
        hstack_pop(stack);
        std::cout << x << " ";
    }
    hstack_destroy(stack);
    std::cout << std::endl;
}
