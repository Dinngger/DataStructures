/**
 * MyQueue.h - The queue.
 * 
 * by Deng Xiaodong - class AI 82
 */

#ifndef __MYQUEUE_H
#define __MYQUEUE_H

#include <stddef.h>

template<typename T>
class MyQueue {
  private:
    T* data;
    size_t head, end, max_size;
  public:
    MyQueue(size_t max_size);
    ~MyQueue();
    bool full() const;
    bool empty() const;
    bool push(const T& d);
    const T& pop();
    const T& peek() const;
    const T* getData() const;
    bool exist(const T& d) const;
};

/**
 * This function init the class.
 * @max_size define the max size of the stack.
 */
template<typename T>
MyQueue<T>::MyQueue(size_t max_size) {
    this->max_size = max_size;
    data = new T[max_size];
    head = 0;
    end = 0;
}

template<typename T>
MyQueue<T>::~MyQueue() {
    delete[] data;
}

template<typename T>
bool MyQueue<T>::full() const {
    return head % max_size == end % max_size && head / max_size != end / max_size;
}

template<typename T>
bool MyQueue<T>::empty() const {
    return head == end;
}

/**
 * This function push T type d into the top of the stack.
 * @param d: The data that will be pushed.
 * @return : bool type: success or not.
 */
template<typename T>
bool MyQueue<T>::push(const T& d) {
    if (!full()) {
        data[head] = d;
        head++;
        head %= 2 * max_size;
    } else {
        return 0;
    }
    return 1;
}

template<typename T>
const T& MyQueue<T>::pop() {
    // assert(!empty());
    size_t _end = end;
    end++;
    end %= 2 * max_size;
    return data[_end];
}

template<typename T>
const T& MyQueue<T>::peek() const {
    // assert(!full());
    return data[end];
}

template<typename T>
const T* MyQueue<T>::getData() const {
    return data;
}

template<typename T>
bool MyQueue<T>::exist(const T& d) const {
    if (empty()) {
        return false;
    } else {
        size_t p = end;
        do {
            if (data[p] == d) {
                return true;
            }
            p++;
            p %= 2 * max_size;
        } while (p != head);
        return false;
    }
}

#endif
