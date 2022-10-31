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

# **list**
### 双向序列容器，用于将它们的元素保持为线性排列，并允许在序列的任何位置插入和删除。

![struct](https://img2022.cnblogs.com/blog/1121656/202210/1121656-20221029111424718-370591967.jpg)
![create_node](https://img2022.cnblogs.com/blog/1121656/202210/1121656-20221029111452581-1489188669.jpg)

### API 
创建和删除一个容器
```
/**
 * 创建一个容器
 * @param type_size 装入容器的数据类型的大小
 * @return 返回新创建的容器
 */
list_ptr_t list_create(uint32_t type_size);

/**
 * 删除给定的容器
 * @param list 一个由 list_create 返回的容器
 */
extern void list_destroy(list_ptr_t list);

/* 装入容器的数据类型为 int */
list_ptr_t list = list_create(sizeof(int));
list_destroy(list);
```
迭代器
```
list_iterator_ptr_t it = list_begin(list);
list_iter_forward(&it);
std::cout << "it = " << DATA_CAST(int)list_iter_data(it) << std::endl;
/* ... */
for (list_iterator_ptr_t it = list_begin(list); it != list_end(list); list_iter_forward(&it)) {
    std::cout << DATA_CAST(int)list_iter_data(it) << " ";
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
list_ptr_t list1 = list_create(sizeof(struct test_str*));
struct test_str* t1 = (struct test_str*)malloc(sizeof (struct test_str));
t1->a = 'a';
t1->b = 10;
list_push_back(list1, &t1, sizeof(t1));
struct test_str* t2 = (struct test_str*)malloc(sizeof (struct test_str));
t2->a = 'b';
t2->b = 20;
list_push_front(list1, &t2, sizeof(t2));

/* ... */
struct test_str t1;
list_ptr_t list2 = list_create(sizeof(struct test_str));
t1.a = 'a';
t1.b = 10;
list_iterator_ptr_t it = list_end(list2);
list_insert(list2, it, &t1, sizeof(t1));
```
删除元素
```
list_pop_back(list);
list_pop_front(list);
```

# **stack**
### stack容器遵循 LIFO（后进先出）语义。 堆栈上最后推送的元素将第一个弹出。
### API 
创建和删除一个容器
```
/**
 * 创建一个 stack 容器
 * @param type_size 装入容器的数据类型的大小。例：`stack_create(sizeof(int));`
 * @return 返回新创建的 stack 容器
 */
stack_ptr_t stack_create(uint32_t type_size);

/**
 * 删除给定的 stack 容器
 * @param stack 一个由 `stack_create` 返回的容器
 */
void stack_destroy(stack_ptr_t stack);

/* ... */
stack_ptr_t stack = list_create();
list_destroy(stack);
```

# **queue**
### queue容器遵循 FIFO（先进先出）语义。 第一个推送（即插入队列中）的元素将第一个弹出（即从队列中删除）。
### API 
创建和删除一个容器
```
/**
 * 创建一个 queue 容器
 * @param type_size 装入容器的数据类型的大小。例：`queue_create(sizeof(int));`
 * @return 返回新创建的 queue 容器
 */
queue_ptr_t queue_create(uint32_t type_size);

/**
 * 删除给定的 queue 容器
 * @param queue 一个由 `queue_create` 返回的容器
 */
void queue_destroy(queue_ptr_t queue);

/* ... */
stack_ptr_t queue = list_create();
list_destroy(queue);
```

---

**1、为什么要写这个库？**<br>
在C语言中，由于不能泛型编程，所以能开箱即用的数据结构很少，一般都要自己造轮子（现在亦是如此）。

**2、如何使用*C*语言进行“泛型”编程？**<br>
虽然在C语言中不能使用模板，但是可以使用万能指针（void*）来替代。

**3、目前有哪些使用方式？**
