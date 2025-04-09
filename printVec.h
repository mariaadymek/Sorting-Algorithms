#ifndef SORTING_PRINTVEC_H
#define SORTING_PRINTVEC_H

#include <ctime>
#include <iostream>
#include <vector>
using std::cout, std::endl, std::vector;

template<typename Comparable>
void printVec(const vector<Comparable> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << v[i];
    }
    cout << endl;
}

#endif
