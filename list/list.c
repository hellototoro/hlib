/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:41
 * @FilePath: /hlibc/list/list.c
 * @Description: None
 * @other: None
 */
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* 初始化列表 */
status_t list_init(link_list *list)
{
    list->head = (list_node_t *) malloc(sizeof (list_node_t));
    if (list->head == NULL) return ERROR;
    list->head->data_ptr = NULL;
    list->head->next = NULL;
    list->size = 0;
    return OK;
}

link_list* list_create(void)
{
    link_list* list = (link_list *) malloc(sizeof (link_list));
    if (list != NULL) list_init(list);
    return list;
}

/*
 node : 插入新节点的位置（位于node节点之后）；
        如果node为NULL，则在表尾插入新节点
 data : 新节点的数据域
*/
status_t list_insert_with_node(link_list *list, list_node_t *node, data_ptr_t data_ptr, int data_size, copy_data_f copy_data)
{
    list_node_t* pre;
    list_node_t* p = list->head;
    do {
        pre = p;
        p = p->next;
    } while (p != NULL && p != node);
    if (p != node) return ERROR;
    list_node_t *new_node = (list_node_t *) malloc(sizeof (list_node_t));
    new_node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL) copy_data(new_node->data_ptr, data_ptr);
    else                   memcpy(new_node->data_ptr, data_ptr, data_size);
    if (p == NULL) p = pre;
    new_node->next = p->next;
    p->next = new_node;
    ++list->size;
    return OK;
}

status_t list_insert_with_index(link_list *list, int index, data_ptr_t data_ptr, int data_size, copy_data_f copy_data)
{
    list_node_t *p = list->head;
    if (index > list_get_size(*list)+1) return ERROR;
    int i;
    for (i = 0; p != NULL && i < index - 1; ++i) p = p->next;
    if (p == NULL || i > index -1) return ERROR;
    list_node_t *new_node = (list_node_t *) malloc(sizeof (list_node_t));
    new_node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL) copy_data(new_node->data_ptr, data_ptr);
    else                   memcpy(new_node->data_ptr, data_ptr, data_size);
    new_node->next = p->next;
    p->next = new_node;
    ++list->size;
    return OK;
}

status_t list_append(link_list *list, data_ptr_t data_ptr, int data_size, copy_data_f copy_data)
{
    return list_insert_with_node(list, NULL, data_ptr, data_size, copy_data);
}

list_node_t *list_get_node(link_list list, int index)
{
    list_node_t *p = list.head->next;
    if (index > list_get_size(list)) return NULL;
    for (int i = 1; p != NULL && i < index; ++i) {
        p = p->next;
    }
    return p;
}

data_ptr_t list_get_data(link_list list, int index)
{
    list_node_t *p = list_get_node(list, index);
    return p != NULL ? p->data_ptr : NULL;
}

status_t list_delete(link_list *list, list_node_t *node)
{
    list_node_t *p = list->head;
    while (p->next != NULL && p->next != node) p = p->next;
    if (p->next == NULL) return ERROR;
    list_node_t *q = p->next;
    p->next = q->next;
    free(q->data_ptr);
    free(q);
    --list->size;
    return OK;
}

status_t list_destroy(link_list *list)
{
    list_node_t *p = list->head;
    do {
        list_node_t* q = p;
        p = p->next;
        free(q->data_ptr);
        free(q);
    } while(p);
    free(list);
    return OK;
}

int list_get_size(link_list list)
{
    return list.size;
}
