/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:07:17
 * @FilePath: /hlibc/common/hcommon.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_HCOMMON_H__
#define __HLIBC_HCOMMON_H__

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
    HLIB_OK          =  1,
    HLIB_ERROR       =  0,
    HLIB_OVERFLOW    = -2
} hlib_status_t;

typedef void* hdata_ptr_t;
typedef void (*copy_data_f)(hdata_ptr_t, const hdata_ptr_t);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
