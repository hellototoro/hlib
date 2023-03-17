/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-17 20:18:07
 * @FilePath: /hlibc/example/list_example.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "../list/hlist.h"

void copy_data(void* dest, const void* src)
{
    int* d =  static_cast<int*>(dest);
    const int* s = static_cast<const int*>(src);
    *d = *s;
}
struct test_str
{
    char a;
    double b;
};

void list_example1(void)
{
    hlist_ptr_t list = hlist_create(sizeof(int));
    
    int a[] = {1,2,3,4,5,6};
    for (unsigned long i = 0; i < sizeof(a)/sizeof(int); ++i) {
        hlist_push_back(list, &a[i], sizeof(a[i]));
    }
    hlist_iterator_ptr_t it = hlist_end(list);
    hlist_iter_backward(&it);
    int b = 10;
    hlist_insert(list, it, &b, sizeof(b));
    std::cout << "it = " << DATA_CAST(int)hlist_iter_data(it) << std::endl;

    for (hlist_iterator_ptr_t it = hlist_begin(list); it != hlist_end(list); hlist_iter_forward(&it)) {
        int x = DATA_CAST(int)hlist_iter_data(it);
        std::cout << x << " ";
    }
    std::cout << std::endl;
    hlist_destroy(list);
    list = nullptr;
}

void list_example2(void)
{
    struct test_str t1;
    hlist_ptr_t list = hlist_create(sizeof(struct test_str));
    t1.a = 'a';
    t1.b = 10;
    hlist_push_back(list, &t1, sizeof(t1));
    hlist_iterator_ptr_t it = hlist_end(list);
    std::cout <<  "a = "<< (DATA_CAST(struct test_str)hlist_iter_data(it)).a << ", b = " << (DATA_CAST(struct test_str)hlist_iter_data(it)).b << " ";
    t1.a = 'b';
    t1.b = 20;
    hlist_push_back(list, &t1, sizeof(t1));
    for (hlist_iterator_ptr_t it = hlist_end(list); it != hlist_end(list); hlist_iter_backward(&it)) {
        struct test_str x = DATA_CAST(struct test_str)hlist_iter_data(it);
        std::cout <<  "a = "<< x.a << ", b = " << x.b << " ";
    }
    std::cout << std::endl;
    hlist_destroy(list);
}

void list_example3(void)
{
    hlist_ptr_t list = hlist_create(sizeof(struct test_str*));
    
    struct test_str* t1 = new struct test_str;
    t1->a = 'a';
    t1->b = 10;
    hlist_push_back(list, &t1, sizeof(t1));
    struct test_str* t2 = new struct test_str;
    t2->a = 'b';
    t2->b = 20;
    hlist_push_back(list, &t2, sizeof(t2));
    
    for (hlist_iterator_ptr_t it = hlist_begin(list); it != hlist_end(list); hlist_iter_forward(&it)) {
        struct test_str *x = DATA_CAST(struct test_str *)hlist_iter_data(it);
        std::cout <<  "a = "<< x->a << ", b = " << x->b << " ";
    }
    std::cout << std::endl;
    hlist_destroy(list);
}
