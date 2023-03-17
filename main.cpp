/*
 * @Author: totoro huangjian921@outlook.com
 * @Date: 2022-10-12 14:04:29
 * @FilePath: /hlibc/main.cpp
 * @Description: None
 * @other: None
 */
#include <iostream>
#include "example/example.h"
#include <list>
using namespace std;

int main(int, char**) {
    cout << "---------list data struct test---------" << endl;
    list_example1();
    //list_example2();
    //list_example3();

    cout << "---------stack data struct test---------" << endl;
    stack_example1();

    cout << "---------queue data struct test---------" << endl;
    queue_example1();
}
