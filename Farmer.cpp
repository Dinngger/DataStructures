/*
 * Farmer.cpp - The second problem in Data Structure book.
 * Use Breadth Priority traversal to find the solution.
 * 
 * Created Date: Wednesday, May 1st 2019, 3:32:42 pm
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include <string>
#include "MyQueue.h"
#include "MyStack.h"

#define MAX_SOLUTION_NUM 3

/**
 * The last four bits stand for the state of objs;
 * 1 stands for north shore while 0 stands for south shore.
 * 4 bits are the farmer, the wolf, the cabbage, and the sheep.
 */
typedef unsigned int StateType;

/**
 * This function return an array which contains four possible
 * states after the state s.
 * @param s: the state that will be changed.
 *        res: an array that will contain the result. Its lenth should be at least four.
 */
StateType* possibleState(StateType s, StateType* res) {
    res[0] = (s & 0b0111) | (~s & 0b1000);
    res[1] = (s & 0b0011) | (~s & 0b1100);
    res[2] = (s & 0b0101) | (~s & 0b1010);
    res[3] = (s & 0b0110) | (~s & 0b1001);
    return res;
}

/**
 * This function return whether the state is safe.
 */
bool isSafe(StateType s) {
    if (s & 0b1000){
        s = ~s;
    }
    return !((s & 0b0001) && (s & 0b0110));
}

std::string showState(StateType s) {
    std::string output;
    static const std::string objs[4] = {"Farmer", "Wolf", "Carrage", "Sheep"};
    const int char_size[4] = {6, 4, 7, 5};
    int char_num = 0;
    output += "North: ";
    for (int i=0; i<4; i++) {
        if (s & 1<<(3-i)) {
            if (char_num != 0) {
                output += ", ";
                char_num += 2;
            }
            output += objs[i];
            char_num += char_size[i];
        }
    }
    for (int i=char_num; i<30; i++) {
        output += ' ';
    }
    char_num = 0;
    output += "South: ";
    for (int i=0; i<4; i++) {
        if (!(s & 1<<(3-i))) {
            if (char_num != 0) {
                output += ", ";
            }
            char_num = 1;
            output += objs[i];
        }
    }
    output += "\n";
    return output;
}

int main() {
    int visited[16] = {0,};   //visited times of each state.
    StateType precursur[16][MAX_SOLUTION_NUM];
    MyQueue<StateType> queue(16);   //storige all posible safe state in the next step.
    StateType nowState;
    visited[0] = 1;
    StateType nextState[4];
    bool failed = false;
    queue.push(0b0000);
    while (!queue.empty()) {
        nowState = queue.pop();
        if (nowState == 0b1111) {
            continue;
        }
        possibleState(nowState, nextState);
        for (int i=0; i<4; i++) {
            if (isSafe(nextState[i])) {
                if (visited[nextState[i]] == 0 || queue.exist(nextState[i])) {
                    if (visited[nextState[i]] == 0) {
                        queue.push(nextState[i]);
                    }
                    for (int j=visited[nextState[i]]; j<MAX_SOLUTION_NUM; j++) {
                        precursur[nextState[i]][j] = nowState;
                    }
                    visited[nextState[i]] += 1;
                }
            }
        }
        if (queue.empty()) {
            failed = true;
            break;
        }
    }
    if (!failed) {
        MyStack<StateType> stateStack(16);
        int solution[16] = {0,};
        int solution_num = 0;
        bool finished;
        do {
            nowState = 0b1111;
            finished = true;
            while (nowState != 0b0000) {
                stateStack.push(nowState);
                if (solution[nowState] < visited[nowState]) {
                    solution[nowState]++;
                    if (solution[nowState] < visited[nowState]) {
                        finished = false;
                    }
                }
                nowState = precursur[nowState][solution[nowState]-1];
            }
            stateStack.push(0b0000);
            solution_num++;
            std::cout << "solution " << solution_num << ":\n";
            for (int step=0; !stateStack.empty(); step++) {
                std::cout << "  Step " << step << ":  " << showState(stateStack.pop());
            }
        } while (!finished);
    }
    return 0;
}
