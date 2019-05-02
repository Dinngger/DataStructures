/*
 * JosephRing.cpp - The fourth problem.
 * 
 * Created Date: Thursday, May 2nd 2019, 9:24:44 am
 * by Deng Xiaodong - class AI 82
 */

#include <iostream>
#include "MyLink.h"

using namespace std;

struct People {
    int id;
    int password;
};

int main() {
    MyLink<People> link;
    int n;
    cout << "Please input the number of people: ";
    cin >> n;
    cout << "Please input the password of each people:\n";

    /* init the link */
    Node<People>* last = link.getHead();
    for (int i=1; i<=n; i++) {
        People person;
        person.id = i;
        cin >> person.password;
        last = link.append(last, person);
    }
    last->next = link.getHead();

    cout << "Please input the ceiling: ";
    int ceiling;
    cin >> ceiling;

    cout << "running...\n";
    Node<People>* pNode = link.getHead();
    while (!link.empty()) {
        for (int i=0; i<ceiling-1; i++) {
            pNode = pNode->next;
        }
        cout << pNode->data.id << ", ";
        ceiling = pNode->data.password;
        pNode = link.delNode(pNode);
    }
    cout << "\nfinished\n";
    return 0;
}
