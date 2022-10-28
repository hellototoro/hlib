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
    list_t list;
    list_init(&list);
    
    int a[] = {1,2,3,4,5,6};
    for (int i = 0; i < 6; ++i) {
        list.push_back(&list, &a[i], sizeof(a[i]));
    }
    list_iterator_t it = list.begin(&list);
    std::cout << "it = " << DATA_CAST(int)it.data(&it) << std::endl;
    int b = 7;
    it.forward(&it);
    list.insert(&it, &b, sizeof(b));

    b = 8;
    it.forward_to(&it, 2);
    list.insert(&it, &b, sizeof(b));
    list.pop_back(&list);
    list.pop_front(&list);

    for (it = list.begin(&list); it.begin != it.end; it.forward(&it)) {
        int x = DATA_CAST(int)it.data(&it);
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void list_example2(void)
{
    struct test_str t1;
    list_t list;
    list_init(&list);
    t1.a = 'a';
    t1.b = 10;
    list.push_back(&list, &t1, sizeof(t1));
    t1.a = 'b';
    t1.b = 20;
    list.push_back(&list, &t1, sizeof(t1));
    for (list_iterator_t it = list.end(&list); it.begin != it.end; it.backward(&it)) {
        struct test_str x = DATA_CAST(struct test_str)it.data(&it);
        std::cout <<  "a = "<< x.a << ", b = " << x.b << " ";
    }
    std::cout << std::endl;
}

void list_example3(void)
{
    list_t list;
    list_init(&list);
    
    struct test_str* t1 = new struct test_str;
    t1->a = 'a';
    t1->b = 10;
    list.push_back(&list, &t1, sizeof(t1));
    struct test_str* t2 = new struct test_str;
    t2->a = 'b';
    t2->b = 20;
    list.push_back(&list, &t2, sizeof(t2));
    
    for (list_iterator_t it = list.begin(&list); it.begin != it.end; it.forward(&it)) {
        struct test_str *x = DATA_CAST(struct test_str *)it.data(&it);
        std::cout <<  "a = "<< x->a << ", b = " << x->b << " ";
    }
    std::cout << std::endl;
}
