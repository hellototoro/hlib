/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-30 22:03:26
 * @FilePath: /hlibc/common/hlibc_type.h
 * @Description: None
 * @other: None
 */
#ifndef __HLIBC_TYPE_H__
#define __HLIBC_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

struct hnode {
    hdata_ptr_t data_ptr;
    struct hnode *next;
};

struct hdnode {
    hdata_ptr_t data_ptr;
    struct hdnode *prev, *next;
};

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
