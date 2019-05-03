/*
 * MyBinaryLink.h
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
    bool deleteTree(BiNode<T>* node);
  public:
    BiLink() {head = nullptr;}
    ~BiLink();
    BiNode<T>* getHead() {return head;}
    BiNode<T>* append(BiNode<T>* node, bool left, const T& d);
};

template<typename T>
/**
 * This function delete the node and all its children.
 * This is not a good function. It will turn into endless recall if
 * there is any circle in the tree, and it will easily run out of memory if
 * the tree is too long.
 */
bool BiLink<T>::deleteTree(BiNode<T>* node) {
    if (node != nullptr) {
        if (node->leftChild != nullptr) {
            deleteTree(node->leftChild);
        }
        if (node->rightChild != nullptr) {
            deleteTree(node->rightChild);
        }
        delete node;
    }
    return true;
}

template<typename T>
BiLink<T>::~BiLink() {
    deleteTree(head);
}

template<typename T>
/**
 * This function created a new Binode with data @param d,
 * and put the new node after @param node.
 * @param left determins it is leftchild or rightchild.
 * Then return the new Binode.
 */
BiNode<T>* BiLink<T>::append(BiNode<T>* node, bool left, const T& d) {
    BiNode<T>* newBiNode = new BiNode<T>;
    newBiNode->data = d;
    newBiNode->leftChild = newBiNode->rightChild = nullptr;
    if (node != nullptr) {
        if (left) {
            node->leftChild = newBiNode;
        } else {
            node->rightChild = newBiNode;
        }
    } else if (head == nullptr) {
        head = newBiNode;
    }
    return newBiNode;
}
