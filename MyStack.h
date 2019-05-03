/**
 * MyStack.h - The stack.
 * 
 * by Deng Xiaodong - class AI 82
 */

#ifndef __MYSTACK_H
#define __MYSTACK_H

#include <stddef.h>

template<typename T>
class MyStack {
  private:
    T* data;
    size_t head, max_size;
  public:
    MyStack(size_t max_size);
    ~MyStack();
    bool full() const {return head >= max_size;}
    bool empty() const {return head == 0;}
    bool push(const T& d);
    const T& pop();
    size_t getSize() const {return head;}
    const T* getData() const;
};

/**
 * This function init the class.
 * @max_size define the max size of the stack.
 */
template<typename T>
MyStack<T>::MyStack(size_t max_size) {
    this->max_size = max_size;
    data = new T[max_size];
    head = 0;
}

template<typename T>
MyStack<T>::~MyStack() {
    delete[] data;
}

/**
 * This function push T type d into the top of the stack.
 * @param d: The data that will be pushed.
 * @return : bool type: success or not.
 */
template<typename T>
bool MyStack<T>::push(const T& d) {
    if (!full()) {
        data[head] = d;
        head++;
    } else {
        return 0;
    }
    return 1;
}

template<typename T>
const T& MyStack<T>::pop() {
    // assert(!empty());
    return data[--head];
}

template<typename T>
const T* MyStack<T>::getData() const {
    return data;
}

#endif
