/*
 * BinaryLookupTree.cpp - The sixth problem.
 * 
 * Created Date: Thursday, May 2nd 2019, 11:44:24 am
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <string>
#include <sstream>
#include "MyBinarySearchTree.h"

using namespace std;

int inOrder(BiNode<KeyNode<int, int>>* root) {
    static int deepth = 0, sum = 0;
    if (root != nullptr) {
        deepth++;
        inOrder(root->leftChild);
        deepth--;
        cout << root->data.data << ' ';
        sum += deepth;
        deepth++;
        inOrder(root->rightChild);
        deepth--;
    }
    return sum;
}

int main() {
    MyBinarySearchTree<int, int> BSTree;
    string input;
    cout << "Please input an int array end with '\\n':\n";
    getline(cin, input);
    stringstream ss;
    ss << input;
    int n = 0;
    while (!ss.eof()) {
        int num;
        ss >> num;
        n++;
        BSTree.insert(num, num);
    }
    cout << "In order:\n";
    BiNode<KeyNode<int, int>>* root = BSTree.getHead();
    int deepth = inOrder(root);
    double avr_deepth = (double)deepth / n;
    cout << "\naverage deepth is " << avr_deepth << '\n';
    cout << "Please enter a number to delete: ";
    int num;
    cin >> num;
    if (!BSTree.deleteNode(num)) {
        cout << "There is no " << num << " !\n";
    } else {
        cout << "In order:\n";
        BiNode<KeyNode<int, int>>* root = BSTree.getHead();
        inOrder(root);
    }
    return 0;
}
