/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:41
 * @FilePath: /hlib/list/list.c
 * @Description: None
 * @other: None
 */
#include <stdlib.h>
#include "list.h"

/* 初始化列表 */
status_t list_init(link_list *list)
{
    list->head = (list_node_t *) malloc(sizeof (list_node_t));
    if (list->head == NULL) return ERROR;
    list->head->data = INIT_VALUE_OF_DATA;
    list->head->next = NULL;
    list->size = 0;
    return OK;
}

/*
 node : 插入新节点的位置（位于node节点之后）；
        如果node为NULL，则在表尾插入新节点
 data : 新节点的数据域
*/
status_t list_insert_with_node(link_list *list, list_node_t *node, data_t data)
{
    list_node_t* pre;
    list_node_t* p = list->head;
    do {
        pre = p;
        p = p->next;
    } while (p != NULL && p != node);
    if (p != node) return ERROR;
    list_node_t *new_node = (list_node_t *) malloc(sizeof (list_node_t));
    new_node->data = data;
    if (p == NULL) p = pre;
    new_node->next = p->next;
    p->next = new_node;
    ++list->size;
    return OK;
}

status_t list_insert_with_index(link_list *list, int index, data_t data)
{
    list_node_t *p = list->head;
    if (index > list_size(*list)+1) return ERROR;
    int i;
    for (i = 0; p != NULL && i < index - 1; ++i) p = p->next;
    if (p == NULL || i > index -1) return ERROR;
    list_node_t *new_node = (list_node_t *) malloc(sizeof (list_node_t));
    new_node->data = data;
    new_node->next = p->next;
    p->next = new_node;
    ++list->size;
    return OK;
}

status_t list_append(link_list *list, data_t data)
{
    return list_insert_with_node(list, NULL, data);
}

list_node_t *list_get_node(link_list list, int index)
{
    list_node_t *p = list.head->next;
    if (index > list_size(list)) return NULL;
    for (int i = 1; p != NULL && i < index; ++i) {
        p = p->next;
    }
    return p;
}

data_t list_get_data(link_list list, int index)
{
    list_node_t *p = list_get_node(list, index);
    return p != NULL ? p->data : INIT_VALUE_OF_DATA;
}

status_t list_delete(link_list *list, list_node_t *node, delete_data_t delete_data)
{
    list_node_t *p = list->head;
    while (p->next != NULL && p->next != node) p = p->next;
    if (p->next == NULL) return ERROR;
    list_node_t *q = p->next;
    p->next = q->next;
    delete_data(q->data);
    free(q);
    --list->size;
    return OK;
}

status_t list_destroy(link_list *list, delete_data_t delete_data)
{
    list_node_t *p = list->head;
    do {
        list_node_t* q = p;
        p = p->next;
        delete_data(q->data);
        free(q);
    } while(p);
    free(list);
    return OK;
}

int list_size(link_list list)
{
    return list.size;
}
