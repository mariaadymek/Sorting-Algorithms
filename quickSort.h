#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "printVec.h"

template<typename Comparable>
void quickSortUnstableRec(vector<Comparable> &vec, int startIndex, int endIndex, Comparable& partition, int& i, int& largerElementIndex, Comparable& temp, unsigned long& reads, unsigned long& allocations) {
    // Recursive base case
    if (startIndex >= endIndex) {
        return;
    }

    // Choose a partition element
    partition = vec[startIndex];
    reads += 1;
    allocations += sizeof(Comparable);

    // Loop through vec from startIndex to endIndex
    // Keep track of where the > partition elements start
    largerElementIndex = startIndex+1;
    allocations += sizeof(int);

    for (i = startIndex+1; i <= endIndex; ++i) {
        reads += 1;
        if (vec[i] <= partition) {
            reads += 1;
            // Swap the smaller/equal item to the left of the larger items
            temp = vec[i];
            reads += 1;
            allocations += sizeof(Comparable);

            vec[i] = vec[largerElementIndex];
            reads += 1;
            vec[largerElementIndex] = temp;
            reads += 1;
            // Update largerElementIndex
            ++largerElementIndex;
        }
    }
    // Swap the partition element into place
    if (startIndex != largerElementIndex-1) {
        temp = vec[startIndex];
        reads += 1;

        vec[startIndex] = vec[largerElementIndex - 1];
        reads += 1;

        vec[largerElementIndex - 1] = temp;
        reads += 1;
    }

    // Uncomment this line if you want to see each iteration
    //printVec(vec);

    // Recursive calls for two halves
    quickSortUnstableRec(vec, startIndex, largerElementIndex-2, partition, i, largerElementIndex, temp,reads, allocations);
    quickSortUnstableRec(vec, largerElementIndex, endIndex, partition, i, largerElementIndex, temp,reads, allocations);
}

template<typename Comparable>
vector<Comparable> quickSortUnstable(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) {
    reads = allocations = 0;
    Comparable partition, temp;
    int i, largerElementIndex;
    // Initial allocations count
    allocations += sizeof(Comparable) * 2 + sizeof(int) * 2;

    quickSortUnstableRec(vec, 0, vec.size() - 1, partition, i, largerElementIndex, temp, reads, allocations);
    return vec;
}

template<typename Comparable>
void quickSortStableRec(vector<Comparable> &vec, unsigned long& reads, unsigned long& allocations) {
    // Recursive base case
    if (vec.size() <= 1) {
        return;
    }

    // Choose a partition element
    Comparable partition = vec[0];

    vector<Comparable> smaller, equal, larger;
    // Loop through vec and populate smaller, equal, larger
    int i;
    for (i = 0; i < vec.size(); ++i) {
        if (vec[i] < partition) {
            smaller.push_back(vec[i]);
        } else if (vec[i] > partition) {
            larger.push_back(vec[i]);
        } else {
            equal.push_back(vec[i]);
        }
    }

    // Recursive calls
    quickSortStableRec(smaller, reads, allocations);
    quickSortStableRec(larger, reads, allocations);

    // Copy elements from smaller, equal, and larger back into vec
    for (i = 0; i < vec.size(); ++i) {
        if (i < smaller.size()) {
            vec[i] = smaller[i];
        } else if (i < smaller.size() + equal.size()) {
            vec[i] = equal[i - smaller.size()];
        } else {
            vec[i] = larger[i - smaller.size() - equal.size()];
        }
    }

    // Uncomment this line if you want to see each iteration
    //printVec(vec);
}

template<typename Comparable>
vector<Comparable> quickSortStable(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) {
    reads = allocations = 0;
    quickSortStableRec(vec, reads, allocations);
    return vec;
}

#endif
