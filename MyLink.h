/*
 * MyLink.h - My single link without head node.
 * 
 * Created Date: Thursday, May 2nd 2019, 1:15:29 am
 * by Deng Xiaodong - class AI 82
 */

#include <stddef.h>

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
class MyLink {
  private:
    Node<T>* head;
  public:
    MyLink() {head = nullptr;}
    ~MyLink();
    Node<T>* getHead() {return head;}
    bool empty() {return head == nullptr;}
    Node<T>* delNode(Node<T>* node);
    Node<T>* findLast(Node<T>* node);
    Node<T>* append(Node<T>* node, const T& d);
};

template<typename T>
MyLink<T>::~MyLink() {
    Node<T>* head_last = findLast(head);
    if (head_last != nullptr) {
        head_last->next = nullptr;
    }
    while (head != nullptr) {
        delNode(head);
    }
}

template<typename T>
/**
 * This function delete @param node, and return the next node if possible.
 * If this node is head, head will be the next node.
 */
Node<T>* MyLink<T>::delNode(Node<T>* node) {
    Node<T>* next = nullptr;
    if (node != nullptr) {
        Node<T>* last = findLast(node);
        if (last != nullptr) {
            if (node->next != node) {
                last->next = node->next;
            } else {
                last->next = nullptr;
            }
        }
        if (head == node) {
            head = node->next;
        }
        next = node->next;
        delete node;
    }
    return next;
}

template<typename T>
/**
 * This function return the node* whose next is @param node.
 * If failed or the node is head return nullptr;
 */
Node<T>* MyLink<T>::findLast(Node<T>* node) {
    Node<T>* p = head;
    do {
        if (p == nullptr) {
            return nullptr;
        } else if (p->next == nullptr) {
            return nullptr;
        } else if (p->next == head && head != node) {
            return nullptr;
        }
        p = p->next;
    } while (p->next != node);
    return p;
}

template<typename T>
/**
 * This function created a new node with data @param d,
 * and put the new node after @param node.
 * Then return the new node.
 * Most times the @param node should be the end node of a link.
 */
Node<T>* MyLink<T>::append(Node<T>* node, const T& d) {
    Node<T>* newNode = new Node<T>;
    newNode->data = d;
    newNode->next = nullptr;
    if (node != nullptr) {
        node->next = newNode;
    } else if (head == nullptr){
        head = newNode;
    }
    return newNode;
}
