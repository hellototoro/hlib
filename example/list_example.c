/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-17 20:18:07
 * @FilePath: /hlibc/example/list_example.c
 * @Description: None
 * @other: None
 */
#include <stdio.h>
#include <stdlib.h>
#include "list/hlist.h"

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
    printf("it = %d\n", DATA_CAST(int)hlist_iter_data(it));

    for (hlist_iterator_ptr_t it = hlist_begin(list); it != hlist_end(list); hlist_iter_forward(&it)) {
        int x = DATA_CAST(int)hlist_iter_data(it);
        printf("%d ", x);
    }
    printf("\n");
    hlist_destroy(list);
}

void list_example2(void)
{
    struct test_str t1;
    hlist_ptr_t list = hlist_create(sizeof(struct test_str));
    t1.a = 'a';
    t1.b = 10;
    hlist_push_back(list, &t1, sizeof(t1));
    hlist_iterator_ptr_t it = hlist_end(list);
    printf("a = %c, b = %f\n", (DATA_CAST(struct test_str)hlist_iter_data(it)).a, (DATA_CAST(struct test_str)hlist_iter_data(it)).b);
    t1.a = 'b';
    t1.b = 20;
    hlist_push_back(list, &t1, sizeof(t1));
    for (hlist_iterator_ptr_t it = hlist_end(list); it != hlist_end(list); hlist_iter_backward(&it)) {
        struct test_str x = DATA_CAST(struct test_str)hlist_iter_data(it);
        printf("a = %c, b = %f\n", x.a, x.b);
    }
    hlist_destroy(list);
}

void list_example3(void)
{
    hlist_ptr_t list = hlist_create(sizeof(struct test_str*));
    
    struct test_str* t1 = (struct test_str*)malloc(sizeof(struct test_str));
    t1->a = 'a';
    t1->b = 10;
    hlist_push_back(list, &t1, sizeof(t1));

    struct test_str* t2 = (struct test_str*)malloc(sizeof(struct test_str));
    t2->a = 'b';
    t2->b = 20;
    hlist_push_back(list, &t2, sizeof(t2));
    
    for (hlist_iterator_ptr_t it = hlist_begin(list); it != hlist_end(list); hlist_iter_forward(&it)) {
        struct test_str *x = DATA_CAST(struct test_str *)hlist_iter_data(it);
        printf("a = %c, b = %f\n", x->a, x->b);
    }

    while (!hlist_empty(list)) {
        struct test_str *x = DATA_CAST(struct test_str *)hlist_back(list);
        hlist_pop_back(list);
        free(x);
    }
    hlist_destroy(list);
}
