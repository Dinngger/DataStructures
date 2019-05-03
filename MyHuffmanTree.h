/*
 * MyHuffmanTree.h - Huffman tree class using binary linked list.
 * 
 * Created Date: Friday, May 3rd 2019, 1:09:36 am
 * by Deng Xiaodong - class AI 82
 */

#ifndef __MYHUFFMANTREE_H
#define __MYHUFFMANTREE_H

#include "MyBinaryLink.h"
#include "MyHeap.h"

template<typename T>
/**
 * After initation, use addNode() to add all node you need.
 * Then use build to create a huffman tree.
 */
class MyHuffmanTree {
  private:
    const size_t max_num;
    BiLink<HeapNode<T>>** forest;
    size_t tree_num;
    MyHeap<BiLink<HeapNode<T>>*> heap;
    BiLink<HeapNode<T>>* popTree(size_t tree);
    bool pushTree(BiLink<HeapNode<T>>* tree);
    BiLink<HeapNode<T>>* combineTree(BiLink<HeapNode<T>>* a, BiLink<HeapNode<T>>* b);
  public:
    MyHuffmanTree(size_t max_size);
    ~MyHuffmanTree();
    bool addNode(T data, int key);
    bool build();
    BiLink<HeapNode<T>>* topTree() const {return forest[0];}
};

template<typename T>
MyHuffmanTree<T>::MyHuffmanTree(size_t max_size):
    max_num(max_size),
    heap(max_size, false) {
    forest = new BiLink<HeapNode<T>>*[max_size];
    tree_num = 0;
}

template<typename T>
MyHuffmanTree<T>::~MyHuffmanTree() {
    for (size_t i=0; i<tree_num; i++) {
        delete forest[i];
    }
    delete[] forest;
}

template<typename T>
/**
 * This function create a new tree into the forest with one node
 * whose key and data are the @param key and data.
 * @return seccess or not.
 */
bool MyHuffmanTree<T>::addNode(T data, int key) {
    if (tree_num < max_num) {
        BiLink<HeapNode<T>>* newTree = new BiLink<HeapNode<T>>;
        HeapNode<T> node;
        node.key = key;
        node.data = data;
        newTree->append(node, true, nullptr);
        forest[tree_num] = newTree;
        tree_num++;
        return true;
    } else {
        return false;
    }
}

template<typename T>
BiLink<HeapNode<T>>* MyHuffmanTree<T>::popTree(size_t tree) {
    // assert(tree < tree_num);
    BiLink<HeapNode<T>>* tempTree = forest[tree];
    forest[tree] = forest[--tree_num];
    return tempTree;
}

template<typename T>
/**
 * @return successful or not.
 */
bool MyHuffmanTree<T>::pushTree(BiLink<HeapNode<T>>* tree) {
    if (tree_num < max_num) {
        forest[tree_num] = tree;
        tree_num++;
        return true;
    } else {
        return false;
    }
}

template<typename T>
BiLink<HeapNode<T>>* MyHuffmanTree<T>::combineTree(BiLink<HeapNode<T>>* a, BiLink<HeapNode<T>>* b) {
    BiNode<HeapNode<T>>* topNode = new BiNode<HeapNode<T>>;
    topNode->leftChild = a->getHead();
    topNode->rightChild = b->getHead();
    topNode->data.key = topNode->leftChild->data.key + topNode->rightChild->data.key;
    BiLink<HeapNode<T>>* newTree = new BiLink<HeapNode<T>>;
    newTree->append(topNode, true, nullptr);
    a->clear();
    b->clear();
    delete a;
    delete b;
    return newTree;
}

template<typename T>
bool MyHuffmanTree<T>::build() {
    for (size_t i=0; i<tree_num; i++) {
        heap.push(forest[i]->getHead()->data.key, forest[i]);
    }
    tree_num = 0;
    while (heap.getSize() > 1) {
        BiLink<HeapNode<T>>* newTree = combineTree(heap.pop(), heap.pop());
        heap.push(newTree->getHead()->data.key, newTree);
    }
    pushTree(heap.pop());
    return true;
}

#endif
