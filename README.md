<!--
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-26 00:17:22
 * @FilePath: /hlibc/README.md
 * @Description: None
 * @other: None
-->
# ***hlibc***
## 基于C语言的通用型数据结构与容器库

---

# **list**
### 双向序列容器，用于将它们的元素保持为线性排列，并允许在序列的任何位置插入和删除。

<p align="center">
  <img src="https://github.com/hellototoro/hlibc/blob/main/resource/struct.jpg">
</p>

<p align="center">
  <img src="https://github.com/hellototoro/hlibc/blob/main/resource/create_node.jpg">
</p>

### API (模仿c++的list容器)
定义并初始化
```
list_t list;
list_init(&list);
```
插入元素
```
int a = 7;
list.push_back(&list, &a, sizeof(a));
/* ... */
list.push_front(&list, &a, sizeof(a));
/* ... */
list_iterator_t it = list.begin(&list);
list.insert(&it, &a, sizeof(a));
```
迭代器
```
for (list_iterator_t it = list.begin(&list); it.begin != it.end; it.forward(&it)) {
    std::cout << DATA_CAST(int)it.data(&it) << " ";
}
/* ... */
it.forward_to(&it, 2);
std::cout << "it = " << DATA_CAST(int)it.data(&it) << std::endl;
```
删除元素
```
list.pop_back(&list);
list.pop_front(&list);
```
---

**1、为什么要写这个库？**<br>
在C语言中，由于不能泛型编程，所以能开箱即用的数据结构很少，一般都要自己造轮子（现在亦是如此）。

**2、如何使用*C*语言进行“泛型”编程？**<br>
虽然在C语言中不能使用模板，但是可以使用万能指针（void*）来替代。

**3、目前有哪些使用方式？**
