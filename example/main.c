/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:04:29
 * @FilePath: /hlibc/main.c
 * @Description: None
 * @other: None
 */
#include <stdio.h>
#include "example.h"

int main(int, char**) {
    printf("---------list data struct test---------\n");
    list_example1();
    list_example2();
    list_example3();

    printf("---------stack data struct test---------\n");
    stack_example1();

    printf("---------queue data struct test---------\n");
    queue_example1();
}
