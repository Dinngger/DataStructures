/*
 * MyHuffmanTreeTest.cpp - test file.
 * 
 * Created Date: Thursday, May 2nd 2019, 11:54:04 pm
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <fstream>
#include "MyHuffmanTree.h"
#include "MyStack.h"

using namespace std;

struct CharCodePair {
    char c;
    char code[20];
};

int encoder(BiNode<HeapNode<char>>* node) {
    static MyStack<char> stack(20);
    if (node->leftChild != nullptr) {
        stack.push('0');
        encoder(node->leftChild);
        stack.pop();
    }
    if (node->rightChild != nullptr) {
        stack.push('1');
        encoder(node->rightChild);
        stack.pop();
    }
    if (node->leftChild == nullptr && node->rightChild == nullptr) {
        cout << node->data.data << " ";
        for (::size_t i=0; i<stack.getSize(); i++) {
            cout << stack.getData()[i];
        }
        cout << endl;
    }
    return 0;
}

int main() {
    MyHuffmanTree<char> huffman_tree(20);
    int key;
    char c;
    cout << "Please input key and char pair. key=0 for stop.\n";
    cin >> key >> c;
    while (key != 0) {
        huffman_tree.addNode(c, key);
        cin >> key >> c;
    }
    huffman_tree.build();
    cout << "encoder:\n";
    encoder(huffman_tree.topTree()->getHead());
    return 0;
}

/* read file test
int main() {
    fstream fin;
    fin.open("Huffman_Test_file/test.bmp", ios::binary | ios::in);
    char c = fin.get();
    while (!fin.eof()) {
        // cout << hex << (0xff & c) << ' ';
        c = fin.get();
    }
    fin.close();
    return 0;
}
*/