#ifndef MERGESORT_H
#define MERGESORT_H

#include "printVec.h"

template<typename Comparable>
void mergeSortRec(vector<Comparable> &vec, int startIndex, int endIndex, vector<Comparable>& temp, int& i, int& leftIndex, int& rightIndex, unsigned long& reads, unsigned long& allocations) {
    // Recursive base case
    if (startIndex >= endIndex) {
        return;
    }

    // Recursive calls for the left and right halves
    int centerIndex = (startIndex + endIndex) / 2;
    mergeSortRec(vec, startIndex, centerIndex,temp, i, leftIndex, rightIndex, reads, allocations);
    mergeSortRec(vec, centerIndex + 1, endIndex,temp, i, leftIndex, rightIndex, reads, allocations);

    // Merge
    i = 0;
    leftIndex = startIndex;
    rightIndex = centerIndex + 1;
    // While leftIndex and rightIndex are in bounds of their half
    while (leftIndex <= centerIndex && rightIndex <= endIndex) {
        reads += 2;
        if (vec[leftIndex] <= vec[rightIndex]) {
            temp[i] = vec[leftIndex];
            reads += 1;
            ++leftIndex;
        } else {
            temp[i] = vec[rightIndex];
            reads += 1;
            ++rightIndex;
        }
        ++i;
    }
    // Now one of the halves is empty and the other half has at least one element left to copy into temp
    while (leftIndex <= centerIndex) {
        temp[i] = vec[leftIndex];
        reads += 1;
        ++leftIndex;
        ++i;
    }
    while (rightIndex <= endIndex) {
        temp[i] = vec[rightIndex];
        reads += 1;
        ++rightIndex;
        ++i;
    }
    // Now everything between startIndex and endIndex is copied into temp
    // Copy everything from temp back into vec
    for (i = 0; i <= endIndex-startIndex; ++i) {
        vec[i + startIndex] = temp[i];
        reads += 1;
    }

    // Uncomment this line if you want to see each iteration
    //printVec(vec);
}

template<typename Comparable>
vector<Comparable> mergeSort(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) {
    reads = allocations = 0;
    vector<Comparable> temp(vec.size());
    allocations += temp.size() * sizeof(Comparable);

    int i, leftIndex, rightIndex;
    allocations += 3 * sizeof(int);

    mergeSortRec(vec, 0, vec.size() - 1, temp, i, leftIndex, rightIndex, reads, allocations);
    return vec;
}

#endif
