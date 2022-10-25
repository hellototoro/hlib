/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 32:37:34
 * @FilePath: /hlibc/queue/queue.c
 * @Description: None
 * @other: None
 */
#include <stdlib.h>
#include <string.h>
#include "queue.h"

link_queue_t* queue_create(void)
{
    link_queue_t* queue = (link_queue_t *) malloc(sizeof (link_queue_t));
    queue_node_t *node = (queue_node_t *) malloc(sizeof (queue_node_t));
    node->data_ptr = NULL;
    node->next = NULL;
    queue->front = queue->rear = node;
    queue->size = 0;
    return queue;
}

status_t queue_push(link_queue_t *queue, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data)
{
    queue_node_t *node = (queue_node_t*) malloc(sizeof (queue_node_t));
    node->data_ptr = (data_ptr_t) malloc(data_size);
    if (copy_data != NULL) copy_data(node->data_ptr, data_ptr);
    else                   memcpy(node->data_ptr, data_ptr, data_size);
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    ++queue->size;
    return OK;
}

status_t queue_pop(link_queue_t *queue)
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

data_ptr_t queue_front(link_queue_t *queue)
{
    return queue->front->next->data_ptr;
}

data_ptr_t queue_rear(link_queue_t *queue)
{
    return queue->rear->data_ptr;
}

bool queue_empty(link_queue_t *queue)
{
    return queue->front == queue->rear ? true : false;
}

void queue_clear(link_queue_t *queue)
{
    while(!queue_empty(queue)) {
        queue_pop(queue);
    }
}

void queue_destroy(link_queue_t *queue)
{
    queue_clear(queue);
    free(queue);
}

uint32_t queue_get_size(link_queue_t *queue)
{
    return queue->size;
}
