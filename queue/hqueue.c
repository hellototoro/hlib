/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 32:37:34
 * @FilePath: /hlibc/queue/hqueue.c
 * @Description: None
 * @other: None
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <string.h>
#include "hqueue.h"
#include "../common/hlibc_type.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct hnode queue_node_t;
struct hqueue {
    uint32_t size;
    queue_node_t *front, *rear;
};

/**********************
 *   GLOBAL VARIABLES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

hqueue_ptr_t hqueue_create(uint32_t type_size)
{
    hqueue_ptr_t queue = (hqueue_ptr_t) malloc(sizeof (struct hqueue));
    queue_node_t *head = (queue_node_t *) malloc(sizeof (queue_node_t));
    head->data_ptr = (hdata_ptr_t) malloc(type_size); /* 为 head 节点分配空间：当 queue 为空的时候，确保正常访问 */
    memset(head->data_ptr, '\0', type_size); /* 使用 '\0' 是为了兼容字符串类型的数据 */
    head->next = NULL;
    queue->front = queue->rear = head;
    queue->size = 0;
    return queue;
}

void hqueue_destroy(hqueue_ptr_t queue)
{
    hqueue_clear(queue);
    free(queue->front->data_ptr);
    free(queue->front);
    free(queue);
}

/*=====================
 * Setter functions
 *====================*/

hlib_status_t hqueue_push(hqueue_ptr_t queue, hdata_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    queue_node_t *node = (queue_node_t*) malloc(sizeof (queue_node_t));
    node->data_ptr = (hdata_ptr_t) malloc(data_size);
    if (copy_data != NULL)
        copy_data(node->data_ptr, data_ptr);
    else
        memcpy(node->data_ptr, data_ptr, data_size);
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    ++queue->size;
    return HLIB_OK;
}

hlib_status_t hqueue_pop(hqueue_ptr_t queue)
{
    if(queue->rear == queue->front) return HLIB_ERROR;
    queue_node_t *p = queue->front->next;
    queue->front->next = p->next;
    if (queue->rear == p) queue->rear = queue->front;
    free(p->data_ptr);
    free(p);
    --queue->size;
    return HLIB_OK;
}

void hqueue_clear(hqueue_ptr_t queue)
{
    while(!hqueue_empty(queue)) {
        hqueue_pop(queue);
    }
}

/*=======================
 * Getter functions
 *======================*/

hdata_ptr_t hqueue_front(hqueue_ptr_t queue)
{
    return !hqueue_empty(queue) ? queue->front->next->data_ptr : queue->front->data_ptr;
}

hdata_ptr_t hqueue_rear(hqueue_ptr_t queue)
{
    return queue->rear->data_ptr;
}

bool hqueue_empty(hqueue_ptr_t queue)
{
    return queue->front == queue->rear ? true : false;
}

uint32_t hqueue_size(hqueue_ptr_t queue)
{
    return queue->size;
}
