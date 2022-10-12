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

typedef struct node {
    data_t data;
    struct node *next;
}node_t, *node_ptr_t;

typedef node_t list_node;

typedef struct {
    int len;
    node_ptr_t head;
} LinkList;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
