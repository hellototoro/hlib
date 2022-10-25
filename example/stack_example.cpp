/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 18:48:08
 * @FilePath: /hlibc/example/stack_example.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "../stack/stack.h"

void stack_example1(void)
{
    link_stack* stack = stack_create();
    int a = 10;
    stack_push(stack, &a, sizeof(a), nullptr);
    a = 20;
    stack_push(stack, &a, sizeof(a), nullptr);
    a = 30;
    stack_push(stack, &a, sizeof(a), nullptr);
    int stack_size = stack_get_size(stack);
    for (auto i = 0; i < stack_size; ++i) {
        int x = DATA_CAST(int)stack_top(stack);
        stack_pop(stack);
        std::cout << x << " ";
    }
    stack_destroy(stack);
    std::cout << std::endl;
}
