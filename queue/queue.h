/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-25 32:37:34
 * @FilePath: /hlibc/queue/queue.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_QUEUE_H__
#define __HLIBC_QUEUE_H__

#include "../common/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef node_t queue_node_t;

typedef struct {
    uint32_t size;
    queue_node_t *front, *rear;
} link_queue_t;

extern link_queue_t* queue_create(void);
extern status_t queue_push(link_queue_t *queue, data_ptr_t data_ptr, uint32_t data_size, copy_data_f copy_data);
extern status_t queue_pop(link_queue_t *queue);
extern data_ptr_t queue_front(link_queue_t *queue);
extern data_ptr_t queue_rear(link_queue_t *queue);
extern bool queue_empty(link_queue_t *queue);
extern void queue_clear(link_queue_t *queue);
extern void queue_destroy(link_queue_t *queue);
extern uint32_t queue_get_size(link_queue_t *queue);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
