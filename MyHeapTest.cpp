/*
 * MyHeapTest.cpp - for test.
 * 
 * Created Date: Friday, May 3rd 2019, 9:44:21 am
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include "MyHeap.h"

using namespace std;

int main() {
    MyHeap<int> myHeap(10, false);
    int key, data, op;
    cin >> op;
    while (op != 0) {
        if (op == 1) {
            cin >> key >> data;
            myHeap.push(key, data);
        } else {
            cout << myHeap.pop() << '\n';
        }
        cin >> op;
    }
    return 0;
}
