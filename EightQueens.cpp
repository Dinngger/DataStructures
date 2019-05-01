/*
 * EightQueens.cpp - The third problem.
 * 
 * Created Date: Thursday, May 2nd 2019, 12:50:16 am
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
using namespace std;

#define N 8

int abs(int i) {
    return i >= 0 ? i : -i;
}

int main() {
    int x[N];   // storage the number of the column on which the queen stands.
    int init_j = 0;
    for (int i=0; i<N; i++) {
        bool i_yes = false;
        for (int j=init_j; j<N; j++) {
            bool j_yes = true;
            for (int ii=0; ii<i; ii++) {
                if (x[ii] == j || abs(j - x[ii]) == i - ii) {
                    j_yes = false;
                    break;
                }
            }
            if (j_yes) {
                i_yes = true;
                x[i] = j;
                break;
            }
        }
        if (!i_yes) {
            init_j = x[--i] + 1;
            i--;
        } else {
            init_j = 0;
        }
    }
    cout << "One solution is:\n";
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (x[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    return 0;
}
