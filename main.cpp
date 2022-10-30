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

    cout << "-------stl list test start--------------" << endl;
    list<int> list;
    list.assign({1,2,3,4,5,6});
    //auto it = list.begin();
    auto it = list.end();
    //++it;
    --it;
    //++it;
    //++it;
    //list.insert(it, 10);
    cout << "it = " << *it << endl;
    for(; it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    for(auto i:list) {
        cout << i << " ";
    }
    cout << endl;
    cout << "-------stl list test end--------------" << endl;

    //cout << "---------stack data struct test---------" << endl;
    //stack_example1();

    //cout << "---------queue data struct test---------" << endl;
    //queue_example1();
}
