/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-17 20:18:07
 * @FilePath: /hlibc/example/list_example.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "../list/list.h"

void copy_data(void* dest, const void* src)
{
    int* d =  static_cast<int*>(dest);
    const int* s = static_cast<const int*>(src);
    *d = *s;
}

struct test_str
{
    char a;
    int b;
};

void list_example1(void)
{
    link_list* list = list_create();
    int a[] = {1,2,3,4,5,6};
    for (int i = 0; i < 6; ++i) {
        list_append(list, &a[i], sizeof(a), copy_data);
    }
    int b = 10;
    list_insert_with_node(list, list_get_node(list, 4), &b, sizeof(b), copy_data);
    int c = 12;
    list_insert_with_index(list, 1, &c, sizeof(c), copy_data);
    for (auto i = 0; i < list_get_size(list); ++i) {
        int *x;
        x = static_cast<int *>(list_get_data(list, i+1));
        std::cout << *x << " ";
    }
    std::cout << std::endl;
    list_destroy(list);
}

void list_example2(void)
{
    struct test_str t1;
    link_list* list = list_create();
    t1.a = 'a';
    t1.b = 10;
    list_append(list, &t1, sizeof(t1), nullptr);
    t1.a = 'b';
    t1.b = 20;
    list_append(list, &t1, sizeof(t1), nullptr);
    for (auto i = 0; i < list_get_size(list); ++i) {
        struct test_str *x;
        x = static_cast<struct test_str *>(list_get_data(list, i+1));
        std::cout <<  "a = "<< x->a << ", b = " << x->b << " ";
    }
    std::cout << std::endl;
    list_destroy(list);
}

void list_example3(void)
{
    link_list* list = list_create();
    
    struct test_str* t1 = new struct test_str;
    t1->a = 'a';
    t1->b = 10;
    list_append(list, &t1, sizeof(t1), nullptr);
    struct test_str* t2 = new struct test_str;
    t2->a = 'b';
    t2->b = 20;
    list_append(list, &t2, sizeof(t2), nullptr);
    for (auto i = 0; i < list_get_size(list); ++i) {
        struct test_str **y = static_cast<struct test_str **>(list_get_data(list, i+1));
        struct test_str *x = *y;
        std::cout <<  "a = "<< x->a << ", b = " << x->b << " ";
    }
    std::cout << std::endl;
    list_destroy(list);
}
