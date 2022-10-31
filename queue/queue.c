/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 32:37:34
 * @FilePath: /hlibc/queue/queue.c
 * @Description: None
 * @other: None
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "../common/hlibc_type.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct node queue_node_t;
struct _queue_t {
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

queue_ptr_t queue_create(void)
{
    queue_ptr_t queue = (queue_ptr_t) malloc(sizeof (struct _queue_t));
    queue_node_t *node = (queue_node_t *) malloc(sizeof (queue_node_t));
    node->data_ptr = NULL;
    node->next = NULL;
    queue->front = queue->rear = node;
    queue->size = 0;
    return queue;
}

void queue_destroy(queue_ptr_t queue)
{
    queue_clear(queue);
    free(queue);
}

/*=====================
 * Setter functions
 *====================*/

status_t queue_push(queue_ptr_t queue, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    queue_node_t *node = (queue_node_t*) malloc(sizeof (queue_node_t));
    node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL)
        copy_data(node->data_ptr, data_ptr);
    else
        memcpy(node->data_ptr, data_ptr, data_size);
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    ++queue->size;
    return OK;
}

status_t queue_pop(queue_ptr_t queue)
{
    if(queue->rear == queue->front) return ERROR;
    queue_node_t *p = queue->front->next;
    queue->front->next = p->next;
    if (queue->rear == p) queue->rear = queue->front;
    free(p->data_ptr);
    free(p);
    --queue->size;
    return OK;
}

void queue_clear(queue_ptr_t queue)
{
    while(!queue_empty(queue)) {
        queue_pop(queue);
    }
}

/*=======================
 * Getter functions
 *======================*/

data_ptr_t queue_front(queue_ptr_t queue)
{
    return queue->front->next->data_ptr;
}

data_ptr_t queue_rear(queue_ptr_t queue)
{
    return queue->rear->data_ptr;
}

bool queue_empty(queue_ptr_t queue)
{
    return queue->front == queue->rear ? true : false;
}

uint32_t queue_size(queue_ptr_t queue)
{
    return queue->size;
}
