/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-17 20:18:07
 * @FilePath: /hlib/example/list_example.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "../list/list.h"

void list_example(void) {
    link_list list;
    list_init(&list);
    int a[] = {1,2,3,4,5,6};
    for (int i = 0; i < 6; ++i) {
        list_append(&list, &a[i], sizeof(int));
    }
    int b = 10;
    list_insert_with_node(&list, list_get_node(list, 4), &b, sizeof(int));
    int c = 12;
    list_insert_with_index(&list, 1, &c, sizeof(int));
    for (auto i = 0; i < list_size(list); ++i) {
        int *x;
        x = static_cast<int *>(list_get_data(list, i+1));
        std::cout << *x << " ";
    }
    std::cout << std::endl;
}
