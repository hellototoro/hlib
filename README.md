<!--
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-26 00:17:22
 * @FilePath: /hlibc/README.md
 * @Description: None
 * @other: None
-->
# ***hlibc***
## 基于C语言的通用型数据结构与容器库
博客地址：[https://www.cnblogs.com/hellototoro/p/16838272.html](https://www.cnblogs.com/hellototoro/p/16838272.html)
---

# **hlist**
### 双向序列容器，用于将它们的元素保持为线性排列，并允许在序列的任何位置插入和删除。

![struct](https://img2022.cnblogs.com/blog/1121656/202210/1121656-20221029111424718-370591967.jpg)
![create_node](https://img2022.cnblogs.com/blog/1121656/202210/1121656-20221029111452581-1489188669.jpg)
！！！对于堆数据来说，本库提供的clear函数不能释放开发者申请的堆空间，开发人员应该自己负责清理申请的堆空间。

### API 
创建和删除一个容器
```
/**
 * 创建一个容器
 * @param type_size 装入容器的数据类型的大小
 * @return 返回新创建的容器
 */
hlist_ptr_t hlist_create(uint32_t type_size);

/**
 * 删除给定的容器
 * @param list 一个由 hlist_create 返回的容器
 */
extern void hlist_destroy(hlist_ptr_t list);

/* 装入容器的数据类型为 int */
hlist_ptr_t list = hlist_create(sizeof(int));
hlist_destroy(list);
```
迭代器
```
hlist_iterator_ptr_t it = hlist_begin(list);
hlist_iter_forward(&it);
std::cout << "it = " << DATA_CAST(int)hlist_iter_data(it) << std::endl;
/* ... */
for (hlist_iterator_ptr_t it = hlist_begin(list); it != hlist_end(list); hlist_iter_forward(&it)) {
    std::cout << DATA_CAST(int)hlist_iter_data(it) << " ";
}
```
插入节点，两种方式插入一个节点：1、在头部或者尾部插入；2、使用迭代器插入
```
struct test_str
{
    char a;
    int b;
};
/* ... */
hlist_ptr_t list1 = hlist_create(sizeof(struct test_str*));
struct test_str* t1 = (struct test_str*)malloc(sizeof (struct test_str));
t1->a = 'a';
t1->b = 10;
hlist_push_back(list1, &t1, sizeof(t1));
struct test_str* t2 = (struct test_str*)malloc(sizeof (struct test_str));
t2->a = 'b';
t2->b = 20;
hlist_push_front(list1, &t2, sizeof(t2));

/* ... */
struct test_str t1;
hlist_ptr_t list2 = hlist_create(sizeof(struct test_str));
t1.a = 'a';
t1.b = 10;
hlist_iterator_ptr_t it = hlist_end(list2);
hlist_insert(list2, it, &t1, sizeof(t1));
```
删除元素
```
hlist_pop_back(list);
hlist_pop_front(list);
```

# **hstack**
### stack容器遵循 LIFO（后进先出）语义。 堆栈上最后推送的元素将第一个弹出。
### API 
创建和删除一个容器
```
/**
 * 创建一个 stack 容器
 * @param type_size 装入容器的数据类型的大小。例：`hstack_create(sizeof(int));`
 * @return 返回新创建的 stack 容器
 */
hstack_ptr_t hstack_create(uint32_t type_size);

/**
 * 删除给定的 stack 容器
 * @param stack 一个由 `hstack_create` 返回的容器
 */
void hstack_destroy(hstack_ptr_t stack);

/* ... */
hstack_ptr_t stack = hlist_create(sizeof(int));
hlist_destroy(stack);
```

# **hqueue**
### queue容器遵循 FIFO（先进先出）语义。 第一个推送（即插入队列中）的元素将第一个弹出（即从队列中删除）。
### API 
创建和删除一个容器
```
/**
 * 创建一个 queue 容器
 * @param type_size 装入容器的数据类型的大小。例：`hqueue_create(sizeof(int));`
 * @return 返回新创建的 queue 容器
 */
hqueue_ptr_t hqueue_create(uint32_t type_size);

/**
 * 删除给定的 queue 容器
 * @param queue 一个由 `hqueue_create` 返回的容器
 */
void hqueue_destroy(hqueue_ptr_t queue);

/* ... */
hstack_ptr_t queue = hlist_create(sizeof(int));
hlist_destroy(queue);
```

---

**1、为什么要写这个库？**<br>
在C语言中，由于不能泛型编程，所以能开箱即用的数据结构很少，一般都要自己造轮子（现在亦是如此）。

**2、如何使用*C*语言进行“泛型”编程？**<br>
虽然在C语言中不能使用模板，但是可以使用万能指针（void*）来替代。

**3、目前有哪些使用方式？**
