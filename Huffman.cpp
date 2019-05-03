/*
 * Huffman.cpp - The eighth problem.
 * 
 * Created Date: Thursday, May 2nd 2019, 11:54:04 pm
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    fstream fin;
    fin.open("Huffman_Test_file/test.bmp", ios::binary | ios::in);
    char c = fin.get();
    while (!fin.eof()) {
        cout << hex << (0xff & c) << ' ';
        c = fin.get();
    }
    fin.close();
    return 0;
}
