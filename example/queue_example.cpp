/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 19:07:37
 * @FilePath: /hlibc/example/queue_example.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "../queue/hqueue.h"

void queue_example1(void)
{
    hqueue_ptr_t queue = hqueue_create(sizeof(int));
    int a = 10;
    hqueue_push(queue, &a, sizeof(a), nullptr);
    a = 20;
    hqueue_push(queue, &a, sizeof(a), nullptr);
    a = 30;
    hqueue_push(queue, &a, sizeof(a), nullptr);
    int size = hqueue_size(queue);
    for (auto i = 0; i < size; ++i) {
        int x = DATA_CAST(int)hqueue_front(queue);
        hqueue_pop(queue);
        std::cout << x << " ";
    }
    hqueue_destroy(queue);
    std::cout << std::endl;
}
