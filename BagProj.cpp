/**
 * BagProj.cpp - The bag problem.
 * The first Data Structure Experiment.
 *
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <string>
#include <sstream>
#include "MyStack.h"

typedef unsigned int volume;

/**
 * After calling the constructor, use getObjects() to init the objects array.
 * if successfully load(), use getBag() to get the solution.
 */
class SmartBag {
private:
    volume max_size;
    size_t obj_num;
    volume* objects;
    MyStack<size_t> bag;
    volume bag_size;        //The size of all objects in the bag now.
    bool finished;
public:
    SmartBag(volume max_size, size_t obj_num);
    ~SmartBag();
    volume* getObjects() {return objects;}      //return *objects for initation.
    bool load();
    std::string getBag() const;
};

SmartBag::SmartBag(volume max_size, size_t obj_num):
    bag(obj_num) {
    this->max_size = max_size;
    this->obj_num = obj_num;
    bag_size = 0;
    objects = new volume[obj_num];
    finished = false;
}

SmartBag::~SmartBag() {
    delete[] objects;
}

/**
 * This function will search next solution when it is once called.
 * @return successful or not.
 */
bool SmartBag::load() {
    static size_t next_obj=0;
    while(!finished) {
        if (bag_size + objects[next_obj] <= max_size) {
            bag.push(next_obj);
            bag_size += objects[next_obj];
            if (bag_size == max_size) {
                return true;
            }
        }
        if (next_obj < obj_num - 1) {
            next_obj++;
        } else {
            do {
                if (bag.empty()) {
                    finished = true;
                    return false;
                }
                next_obj = bag.pop() + 1;
                bag_size -= objects[next_obj-1];
            }while (next_obj >= obj_num);
        }
    }
    return false;
}

std::string SmartBag::getBag() const {
    std::stringstream ss;
    std::string s_bag;
    for (size_t i=0; i<bag.getSize(); i++) {
        ss << objects[bag.getData()[i]];
        if (i != bag.getSize() - 1) {
            ss << ",";
        }
    }
    ss >> s_bag;
    return s_bag;
}

int main() {
    using namespace std;
    ::size_t max_size, obj_num;
    cout << "Please input the max size of the bag: ";
    cin >> max_size;
    cout << "Please input the number of objects: ";
    cin >> obj_num;
    SmartBag smartBag0(max_size, obj_num);
    cout << "Please input " << obj_num << " objects' volume:\n";
    for (::size_t i=0; i<obj_num; i++) {
        cin >> smartBag0.getObjects()[i];
    }
    int solution_num;
    for (solution_num=0; smartBag0.load(); solution_num++) {
        cout << "solution " << solution_num << ": (" << smartBag0.getBag() << ")\n";
    }
    if (solution_num == 0) {
        cout << "No solution!\n";
    }
    return 0;
}
