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

struct node {
    data_ptr_t data_ptr;
    struct node *next;
};

struct dnode {
    data_ptr_t data_ptr;
    struct dnode *prev, *next;
};

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
