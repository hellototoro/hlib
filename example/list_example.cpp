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
    double b;
};

void list_example1(void)
{
    list_ptr_t list = list_create(sizeof(int));
    
    int a[] = {1,2,3,4,5,6};
    for (int i = 0; i < sizeof(a)/sizeof(int); ++i) {
        list_push_back(list, &a[i], sizeof(a[i]));
    }
    //list_iterator_ptr_t it = list_begin(list);
    list_iterator_ptr_t it = list_end(list);
    //list_iter_forward(&it);
    list_iter_backward(&it);
    //list_iter_forward(&it);
    //list_iter_forward(&it);
    int b = 10;
    //list_insert(list, it, &b, sizeof(b));
    std::cout << "it = " << DATA_CAST(int)list_iter_data(it) << std::endl;

    /*b = 8;
    list_iter_forward_to(&it, 3);
    list_insert(list, it, &b, sizeof(b));*/
    //list_pop_back(list);
    //list_pop_front(list);

    for (; it != list_end(list); list_iter_forward(&it)) {
        int x = DATA_CAST(int)list_iter_data(it);
        std::cout << x << " ";
    }
    std::cout << std::endl;
    for (list_iterator_ptr_t it = list_begin(list); it != list_end(list); list_iter_forward(&it)) {
        int x = DATA_CAST(int)list_iter_data(it);
        std::cout << x << " ";
    }
    std::cout << std::endl;
    list_destroy(list);
    list = nullptr;
}

void list_example2(void)
{
    struct test_str t1;
    list_ptr_t list = list_create(sizeof(struct test_str));
    t1.a = 'a';
    t1.b = 10;
    //list_push_back(list, &t1, sizeof(t1));
    list_iterator_ptr_t it = list_end(list);
    std::cout <<  "a = "<< (DATA_CAST(struct test_str)list_iter_data(it)).a << ", b = " << (DATA_CAST(struct test_str)list_iter_data(it)).b << " ";
    t1.a = 'b';
    t1.b = 20;
    //list_push_back(list, &t1, sizeof(t1));
    for (list_iterator_ptr_t it = list_end(list); it != list_end(list); list_iter_backward(&it)) {
        struct test_str x = DATA_CAST(struct test_str)list_iter_data(it);
        std::cout <<  "a = "<< x.a << ", b = " << x.b << " ";
    }
    std::cout << std::endl;
    list_destroy(list);
}

void list_example3(void)
{
    list_ptr_t list = list_create(sizeof(struct test_str*));
    
    struct test_str* t1 = new struct test_str;
    t1->a = 'a';
    t1->b = 10;
    list_push_back(list, &t1, sizeof(t1));
    struct test_str* t2 = new struct test_str;
    t2->a = 'b';
    t2->b = 20;
    list_push_back(list, &t2, sizeof(t2));
    
    for (list_iterator_ptr_t it = list_begin(list); it != list_end(list); list_iter_forward(&it)) {
        struct test_str *x = DATA_CAST(struct test_str *)list_iter_data(it);
        std::cout <<  "a = "<< x->a << ", b = " << x->b << " ";
    }
    std::cout << std::endl;
    list_destroy(list);
}
