/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:54
 * @FilePath: /hlib/list/list.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIB_LIST_H__
#define __HLIB_LIST_H__

#include "../common/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef node_t list_node_t;

/* 带头节点的列表 */
typedef struct {
    int size;
    list_node_t* head;
} link_list;

status_t list_init(link_list *list);
status_t list_insert_with_node(link_list *list, list_node_t *node, data_ptr_t data_ptr, int data_size);
status_t list_insert_with_index(link_list *list, int index, data_ptr_t data_ptr, int data_size);
status_t list_append(link_list *list, data_ptr_t data_ptr, int data_size);
list_node_t *list_get_node(link_list list, int index);
data_ptr_t list_get_data(link_list list, int index);
status_t list_delete(link_list *list, list_node_t *node);
status_t list_destroy(link_list *list);
int list_size(link_list list);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
