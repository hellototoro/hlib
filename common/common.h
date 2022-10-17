/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:07:17
 * @FilePath: /hlib/common/common.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIB_COMMON_H__
#define __HLIB_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OK          =  1,
    ERROR       =  0,
    OVERFLOW    = -2
} status_t;
typedef void* data_t;
typedef void (*delete_data_t) (data_t data);

#define INIT_VALUE_OF_DATA  NULL;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
