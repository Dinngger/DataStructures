/*
 * Huffman_Decode.cpp
 * 
 * Created Date: Saturday, May 4th 2019, 12:08:46 pm
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <fstream>
#include <string>
#include "MyBinaryLink.h"
#include "MyStack.h"

class Decoder {
  private:
    BiLink<char> huffman;
    ::size_t end_len;   // the depth in the tree of the end char '\0', also the max depth.
    ::size_t depth;     // the depth now.
    BiNode<char>* now;
    MyStack<BiNode<char>*> stack;
    char state;
    bool goLeft();
    bool goBack(char c);
    bool goRight();
  public:
    bool is_end_len(::size_t len) const {return len == end_len;}
    BiNode<char>* head;
    Decoder();
    int build(char c);
};

Decoder::Decoder():
    stack(100) {
    head = now = huffman.append(' ', true, nullptr);
    end_len = depth = 0;
    state = '0';
}

bool Decoder::goLeft() {
    depth++;
    state = '0';
    stack.push(now);
    now = huffman.append(' ', true, now);
    return true;
}

bool Decoder::goBack(char c) {
    depth--;
    state = 'd';
    now->data = c;
    if (!stack.empty()) {
        now = stack.pop();
    } else {
        return false;
    }
    return true;
}

bool Decoder::goRight() {
    depth++;
    state = '1';
    now = huffman.append(' ', false, now);
    return true;
}

/**
 * state: '0' : wait for 0 or data. next 1, turn to error 0x01.
 *        '1' : wait for 0 or data. next 1 is data.
 *        'd' : wait for 1.
 *        '$' : wait for $ to comfirm stop byte.
 * error:
 *       0x01 : next 1 : this 1 is data.
 *              else   : last 0 is data.
 * 
 * @return 0 : finished
 *         1 : continue
 *        -1 : error
 *         2 : finished and left the char.
 */
int Decoder::build(char c) {
    int _c = 0xff & c;
    // std::cout << hex << (0xff & c) << ' ' << state << ", ";
    switch (state) {
        case '0':
            if (_c == 0xdd) {
                goLeft();
            } else if (_c == 0xee) {
                state = 0x01;
            } else {
                if (c == '$') {
                    state = '$';
                } else {
                    goBack(c);
                }
            }
            break;
        case 0x01:
            if (_c == 0xee) {
                if (!goBack(0xee)) {
                    std::cout << "error 011\n";
                    return -1;
                }
            } else {
                delete now;
                now = stack.pop();
                now->leftChild = nullptr;
                now->data = 0xdd;
                goRight();
            }
        case '$':
            if (c == '$') {
                end_len = depth;
                if (!goBack('\0')) {
                    return 0;
                }
                break;
            } else {
                if (!goBack('$')) {
                    return 2;
                }
            }
        case '1':
            if (_c == 0xdd) {
                goLeft();
            } else {
                if (c == '$') {
                    state = '$';
                } else {
                    if (!goBack(c)) {
                        return 0;
                    }
                }
            }
            break;
        case 'd':
            if (_c == 0xee) {
                goRight();
            } else {
                std::cout << "error d1\n";
                return -1;
            }
            break;
        default:
            break;
    }
    return 1;
}

int main() {
    std::fstream fin;
    std::string file_name;
    std::cout << "Please input the file name in floder Huffman_zip_file:\n";
    std::cin >> file_name;
    fin.open("Huffman_zip_file/" + file_name + ".huffman", std::ios::binary | std::ios::in);
    std::fstream fout;
    fout.open("Huffman_unzip_file/unzip_" + file_name, std::ios::binary | std::ios::out);
    Decoder decoder;
    bool build_finished = false;
    BiNode<char>* node;
    ::size_t file_counter = 0;
    ::size_t bit_cnt = 0;
    ::size_t depth = 0;
    char c = fin.get();
    bool begin = false;
    bool finished = false;
    while (!fin.eof()) {
        std::cout << std::hex << (0xff & c) << ' ';
        begin = false;
        if (!build_finished) {
            switch (decoder.build(c)) {
                case 0:
                    build_finished = true;
                    node = decoder.head;
                    break;
                case -1:
                    std::cout << "error\n";
                    return -1;
                    break;
                case 2:
                    build_finished = true;
                    node = decoder.head;
                    begin = true;
                    std::cout << "continue: ";
                    break;
                default:
                    break;
            }
        } else {
            begin = true;
        }
        if (begin && !finished) {
            bit_cnt = 0;
            while (bit_cnt < 8) {
                if (c & (1 << (7 - bit_cnt))) {
                    node = node->rightChild;
                    depth++;
                } else {
                    node = node->leftChild;
                    depth++;
                }
                if (node->leftChild == nullptr) {
                    if (node->data == '\0' && decoder.is_end_len(depth)) {
                        finished = true;
                        break;
                    }
                    fout.put(node->data);
                    std::cout  << '|' << std::hex << (0xff & node->data) << ' ';
                    file_counter++;
                    if (!(file_counter % 10000)) {
                        std::cout << file_counter / 1000 << " kb have write ...\n";
                    }
                    node = decoder.head;
                    depth = 0;
                }
                bit_cnt++;
            }
        }
        c = fin.get();
    }
    fout.close();
    fin.close();
    std::cout << "\nfinished!\n";
    return 0;
}
