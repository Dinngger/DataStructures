/*
 * MyHeap.h
 * Use seqList complete binary tree.
 * 
 * Created Date: Friday, May 3rd 2019, 1:21:00 am
 * by Deng Xiaodong - class AI 82
 */

#include <stddef.h>

template<typename T>
struct HeapNode {
    int key;
    T data;
};

template<typename T>
class Heap {
  private:
    HeapNode<T>* heap;
    const size_t max_size;
    const bool maxHeap;   // Define whether it's max heap or min heap.
    size_t heap_size;
    size_t getParent(size_t node) const {return node > 0 ? (node - 1) / 2 : 0;}
    size_t getLeftChild(size_t node) const {return 2 * node + 1;}
    size_t getRightChild(size_t node) const {return 2 * node + 2;}
    bool siftDown(size_t node);
  public:
    Heap(size_t max_size, bool maxHeap);
    ~Heap() {delete[] heap;}
    bool push(int key, const T& data);
    T pop();
};

/**
 * @param max_size determins the max size of the heap.
 * @param maxHeap determins whether it's max heap or min heap.
 */
template<typename T>
Heap<T>::Heap(size_t max_size, bool maxHeap):
    max_size(max_size),
    maxHeap(maxHeap) {
    heap = new HeapNode<T>[max_size];
    heap_size = 0;
}

template<typename T>
bool Heap<T>::siftDown(size_t node) {
    if (node < heap_size) {
        HeapNode<T> tempNode = heap[node];
        while (getLeftChild(node) < heap_size) {
            size_t child = getLeftChild(node);
            if (child < heap_size - 1 && heap[child].key < heap[child + 1].key) {
                child++;
            }
            if (tempNode.key >= heap[child].key) {
                break;
            }
            heap[node] = heap[child];
            node = child;
        }
        heap[node] = tempNode;
        return true;
    } else {
        return false;
    }
}

/**
 * This function create a new node with @param key and @param data,
 * and put it into the heap.
 * @return successful or not.
 */
template<typename T>
bool Heap<T>::push(int key, const T& data) {
    if (heap_size < max_size) {
        size_t newNode = heap_size;
        heap_size++;
        int parentKey = newNode == 0 ? key : heap[getParent(newNode)].key;
        while (maxHeap ? (key > parentKey) : (key < parentKey)) {
            heap[newNode] = heap[getParent(newNode)];
            newNode = getParent(newNode);
            parentKey = newNode == 0 ? key : heap[getParent(newNode)].key;
        }
        heap[newNode].key = key;
        heap[newNode].data = data;
        return true;
    } else {
        return false;
    }
}

/**
 * This function remove the top node of the heap,
 * and @return its data.
 */
template<typename T>
T Heap<T>::pop(){
    // assert(heap_size > 0);
    T data = heap[0].data;
    heap_size--;
    if (heap_size > 0) {
        heap[0] = heap[heap_size];
        siftDown(0);
    }
    return data;
}
