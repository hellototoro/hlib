/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:02:41
 * @FilePath: /hlib/list/list.c
 * @Description: None
 * @other: None
 */
#include "list.h"

/* list */
status_t InitList(LinkList *L)
{
    L->head = (node_t *) malloc(sizeof (node_t));
    L->head->next = NULL;
    L->len = 0;
    return OK;
}

status_t ListAppend(LinkList *L, ElemType e)
{
    Node *p = L->head;
    while (p->next) {
        p = p->next;
    }
    node_t* s = (node_t *) malloc(sizeof (node_t));
    s->data = e;
    s->next = NULL;
    p->next = s;
    L->len++;
    return OK;
}

node_t* ListHead(LinkList *L)
{
    return L->head;
}

status_t DestroyList(LinkList *L)
{
    node_t *p = L->head;
    while(p) {
        node_t* q = p;
        p = p->next;
        free(q);
    }
    free(L);
    L = NULL;
    return OK;
}
