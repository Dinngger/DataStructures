/*
 * MyBinarySearchTree.h
 * 
 * Created Date: Friday, May 3rd 2019, 4:47:35 pm
 * by Deng Xiaodong - class AI 82
 */

#ifndef __MYBINARYSEARCHTREE_H
#define __MYBINARYSEARCHTREE_H

#include "MyBinaryLink.h"

template<typename NumType, typename T>
struct KeyNode {
    NumType id;
    T data;
};

template<typename NumType, typename T>
/**
 * left child has smaller id.
 */
class MyBinarySearchTree {
  private:
    BiLink<KeyNode<NumType, T>> tree;
    BiNode<KeyNode<NumType, T>>* findParent(NumType id);
  public:
    BiNode<KeyNode<NumType, T>>* getHead() {return tree.getHead();}
    T* operator[](NumType id);
    BiNode<KeyNode<NumType, T>>* search(NumType id);
    bool insert(NumType id, T data);
    bool deleteNode(NumType id);
};

template<typename NumType, typename T>
BiNode<KeyNode<NumType, T>>* MyBinarySearchTree<NumType, T>::search(NumType id) {
    BiNode<KeyNode<NumType, T>>* pNode = tree.getHead();
    while (pNode != nullptr) {
        if (pNode->data.id < id) {
            pNode = pNode->rightChild;
        } else if (pNode->data.id > id) {
            pNode = pNode->leftChild;
        } else {
            return pNode;
        }
    }
    return nullptr;
}

template<typename NumType, typename T>
T* MyBinarySearchTree<NumType, T>::operator[](NumType id) {
    BiNode<KeyNode<NumType, T>>* node = search(id);
    if (node == nullptr) {
        return nullptr;
    } else {
        return &(node->data.data);
    }
}

template<typename NumType, typename T>
BiNode<KeyNode<NumType, T>>* MyBinarySearchTree<NumType, T>::findParent(NumType id) {
    BiNode<KeyNode<NumType, T>>* pNode = tree.getHead(),
                               * parent = nullptr;
    while (pNode != nullptr) {
        if (pNode->data.id < id) {
            parent = pNode;
            pNode = pNode->rightChild;
        } else if (pNode->data.id > id) {
            parent = pNode;
            pNode = pNode->leftChild;
        } else {
            return parent;
        }
    }
    return nullptr;
}

template<typename NumType, typename T>
bool MyBinarySearchTree<NumType, T>::insert(NumType id, T data) {
    KeyNode<NumType, T> node;
    node.id = id;
    node.data = data;
    if (tree.getHead() == nullptr) {
        tree.append(node, true, nullptr);
    } else {
        BiNode<KeyNode<NumType, T>>* pNode = tree.getHead();
        BiNode<KeyNode<NumType, T>>* childNode = pNode;
        while (childNode != nullptr) {
            pNode = childNode;
            if (pNode->data.id < id) {
                childNode = pNode->rightChild;
            } else if (pNode->data.id > id) {
                childNode = pNode->leftChild;
            } else {
                return false;
            }
        }
        tree.append(node, pNode->data.id > id, pNode);
    }
    return true;
}

template<typename NumType, typename T>
bool MyBinarySearchTree<NumType, T>::deleteNode(NumType id) {
    BiNode<KeyNode<NumType, T>>* node = search(id);
    if (node == nullptr) {
        return false;
    } else {
        BiNode<KeyNode<NumType, T>>* parent = findParent(id),
                                   * child,
                                   * ptr = node;
        if (ptr->leftChild != nullptr && ptr->rightChild != nullptr) {
            // find the minist node @ptr in right tree, and exchange @ptr with @node.
            parent = ptr;
            ptr = ptr->rightChild;
            while (ptr->leftChild != nullptr) {
                parent = ptr;
                ptr = ptr->leftChild;
            }
            node->data = ptr->data;
        }
        child = ptr->leftChild != nullptr ? ptr->leftChild : ptr->rightChild;
        if (parent == nullptr) {
            tree.setHead(child);
        } else {
            if (parent->leftChild == ptr) {
                parent->leftChild = child;
            } else {
                parent->rightChild = child;
            }
        }
        delete ptr;
        return true;
    }
}

#endif
