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
    Heap<int> myHeap(10, true);
    int key, data;
    for (int i=0; i<5; i++) {
        cin >> key >> data;
        cout << "got " << i + 1 << "\n";
        myHeap.push(key, data);
    }
    cout << "give you: ";
    for (int i=0; i<5; i++) {
        data = myHeap.pop();
        cout << data << " ";
    }
    return 0;
}
