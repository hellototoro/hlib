/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 19:07:37
 * @FilePath: /hlibc/example/queue_example.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "../queue/queue.h"

void queue_example1(void)
{
    link_queue_t *queue = queue_create();
    int a = 10;
    queue_push(queue, &a, sizeof(a), nullptr);
    a = 20;
    queue_push(queue, &a, sizeof(a), nullptr);
    a = 30;
    queue_push(queue, &a, sizeof(a), nullptr);
    int queue_size = queue_get_size(queue);
    for (auto i = 0; i < queue_size; ++i) {
        int x = DATA_CAST(int)queue_front(queue);
        queue_pop(queue);
        std::cout << x << " ";
    }
    queue_destroy(queue);
    std::cout << std::endl;
}
