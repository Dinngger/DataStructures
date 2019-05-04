/*
 * Huffman_Encode.cpp - The ninth problem.
 * 
 * Created Date: Friday, May 3rd 2019, 4:08:47 pm
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <fstream>
#include <string>
#include "MyHuffmanTree.h"
#include "MyBinarySearchTree.h"
#include "MyStack.h"

using namespace std;

struct Code {
    ::size_t len;
    ::size_t code;
};

class Encoder {
  private:
    MyStack<char> stack;
    MyBinarySearchTree<::size_t, Code> BSTree;
    char decoder[1024];
    ::size_t decoder_size;
  public:
    ::size_t get_decoder_size() const {return decoder_size;}
    const char* get_decoder() const {return decoder;}
    Code operator[](::size_t index) {return *BSTree[index];}
    Encoder(::size_t max_size) : stack(max_size) {decoder_size = 0;}
    int encode(BiNode<HeapNode<char>>* node);
};

int Encoder::encode(BiNode<HeapNode<char>>* node) {
    if (node->leftChild != nullptr) {
        stack.push('0');
        decoder[decoder_size++] = 0xdd;
        encode(node->leftChild);
        stack.pop();
    }
    if (node->rightChild != nullptr) {
        stack.push('1');
        decoder[decoder_size++] = 0xee;
        encode(node->rightChild);
        stack.pop();
    }
    if (node->leftChild == nullptr && node->rightChild == nullptr) {
        ::size_t id = 0xff & node->data.data;
        if (node->data.key == 0) {
            id = 0x100;
            decoder[decoder_size++] = '$';
            decoder[decoder_size++] = '$';
        } else {
            decoder[decoder_size++] = node->data.data;
        }
        Code code = {0, 0};
        cout << id << "\t:\t";
        for (::size_t i=0; i<stack.getSize(); i++) {
            code.len++;
            code.code = (code.code << 1) | (0x1 & stack.getData()[i]);
            cout << stack.getData()[i];
        }
        cout << endl;
        BSTree.insert(id, code);
    }
    return 0;
}

int main() {
    fstream fin;
    string file_name;
    cout << "Please input the file name in floder Huffman_Test_file:\n";
    cin >> file_name;
    ::size_t counter[256] = {0,};
    fin.open("Huffman_Test_file/" + file_name, ios::binary | ios::in);
    char c = fin.get();
    while (!fin.eof()) {
        counter[0xff & c]++;
        cout << hex << (0xff & c) << ' ';
        c = fin.get();
    }
    cout << endl;
    MyHuffmanTree<char> huffman_tree(256);
    for (::size_t i=0; i<256; i++) {
        if (counter[i] != 0) {
            huffman_tree.addNode((char)i, counter[i]);
        }
    }
    huffman_tree.addNode((char)0x100, 0); //set as a stop byte.
    huffman_tree.build();
    Encoder encoder(100);
    cout << "encode table:\n";
    encoder.encode(huffman_tree.topTree()->getHead());
    fstream fout;
    fin.clear();
    fin.seekg(ios::beg);
    fout.open("Huffman_zip_file/" + file_name + ".huffman", ios::binary | ios::out);
    const char* decoder = encoder.get_decoder();
    for (::size_t i=0; i<encoder.get_decoder_size(); i++) {
        fout.put(decoder[i]);
        cout << (0xff & decoder[i]) << ' ';
    }
    Code write_char = {0, 0};
    c = fin.get();
    while (!fin.eof()) {
        // cout << (0xff & c) << ' ';
        Code cc = encoder[0xff & c];
        while (cc.len > 0) {
            write_char.len++;
            cc.len--;
            write_char.code = (write_char.code << 1) | (((0x1 << cc.len) & cc.code) >> cc.len);
            if (write_char.len == 8) {
                fout.put((char)write_char.code);
                cout << write_char.code << ' ';
                write_char.len = 0;
                write_char.code = 0x0;
            }
        }
        c = fin.get();
    }
    Code cc = encoder[0x100];
    while (cc.len > 0) {
        write_char.len++;
        cc.len--;
        write_char.code = (write_char.code << 1) | (((1 << cc.len) & cc.code) >> cc.len);
        if (write_char.len == 8) {
            fout.put((char)write_char.code);
            cout << write_char.code << ' ';
            write_char.len = 0;
            write_char.code = 0x0;
        }
    }
    if (write_char.len > 0) {
        fout.put((char)(write_char.code << (8 - write_char.len)));
        cout << write_char.code << (8 - write_char.len) << ' ';
    }
    fout.close();
    fin.close();
    cout << "\nfinished!\n";
    return 0;
}
