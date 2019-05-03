/*
 * Huffman.cpp - The ninth problem.
 * 
 * Created Date: Friday, May 3rd 2019, 4:08:47 pm
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <fstream>
#include "MyHuffmanTree.h"
#include "MyStack.h"

using namespace std;

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
