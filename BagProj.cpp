/**
 * BagProj.cpp - The bag problem.
 * The first Data Structure Experiment.
 *
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include "MyQueue.h"

typedef unsigned int volume;

class SmartBag {
  private:
    volume max_size;
    volume* objects;
    MyQueue<volume> bag;
  public:
    SmartBag(volume max_size, size_t obj_num);
    ~SmartBag();
    volume* getObjects();
    bool load();
};

SmartBag::SmartBag(volume max_size, size_t obj_num):
    bag(obj_num) {
    this->max_size = max_size;
    objects = new volume[obj_num];
}

SmartBag::~SmartBag() {
    delete[] objects;
}

int main() {
    std::cout << "Hello world!\n";
    return 0;
}
