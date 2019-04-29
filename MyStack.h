/**
 * MyStack.h - The stack class.
 * 
 * by Deng Xiaodong - class AI 82
 */

#include <cstddef>

template<typename T>
class MyStack {
  private:
    T* data;
    size_t head, end, max_size;
  public:
    MyStack(size_t max_size);
    ~MyStack();
    bool full() const;
    bool empty() const;
    bool push(const T& d);
    const T& pop();
    const T& peek() const;
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
    end = 0;
}

template<typename T>
MyStack<T>::~MyStack() {
    delete[] data;
}

template<typename T>
bool MyStack<T>::full() const {
    return head % max_size == end % max_size && head / max_size != end / max_size;
}

template<typename T>
bool MyStack<T>::empty() const {
    return head == end;
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
        head %= 2 * max_size;
    } else {
        return 0;
    }
    return 1;
}

template<typename T>
const T& MyStack<T>::pop() {
    assert(!empty);
    size_t _end = end;
    end++;
    end %= 2 * max_size;
    return data[_end];
}

template<typename T>
const T& MyStack<T>::peek() const {
    assert(!full);
    return data[end];
}
