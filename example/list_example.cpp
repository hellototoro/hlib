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
        list_append(&list, &a[i]);
    }
    int c = 10;
    std::cout << *static_cast<int *>(list_get_data(list, 4)) << std::endl;
    list_insert(&list, list_get_node(list, 4), &c);
    for (auto i = 0; i < list_size(list); ++i) {
        int *b;
        b = static_cast<int *>(list_get_data(list, i+1));
        std::cout << *b << " ";
    }
    std::cout << std::endl;
}
