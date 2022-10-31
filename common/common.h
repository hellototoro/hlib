/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:07:17
 * @FilePath: /hlibc/common/common.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_COMMON_H__
#define __HLIBC_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*********************
 *      MACROS
 *********************/
#define DATA_CAST(data_type)        *(data_type*)

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    OK          =  1,
    ERROR       =  0,
    OVERFLOW    = -2
} status_t;

typedef void* data_ptr_t;
typedef void (*copy_data_f)(data_ptr_t, const data_ptr_t);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
