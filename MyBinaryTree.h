/*
 * MyBinaryTree.h
 * This file contains two kinds of binary tree.
 * One uses linked list, one uses seq list.
 * 
 * Created Date: Thursday, May 2nd 2019, 11:58:28 am
 * by Deng Xiaodong - class AI 82
 */

#include <stddef.h>

template<typename T>
struct BiNode {
    T data;
    BiNode* leftChild;
    BiNode* rightChild;
};

template<typename T>
class BiLink {
  private:
    BiNode<T>* head;
  public:
    BiLink() {head = nullptr;}
    ~BiLink();
    BiNode<T>* getHead() {return head;}
    BiNode<T>* find();
    BiNode<T>* append(BiNode<T>* Binode, const T& d);
};

template<typename T>
BiLink<T>::~BiLink() {
}


template<typename T>
/**
 * This function created a new Binode with data @param d,
 * and put the new Binode after @param Binode.
 * Then return the new Binode.
 * Most times the @param Binode should be the end Binode of a link.
 */
BiNode<T>* BiLink<T>::append(BiNode<T>* Binode, const T& d) {
}
