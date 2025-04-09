#ifndef SORTING_BUBBLESORT_H
#define SORTING_BUBBLESORT_H

#include "printVec.h"

template<typename Comparable>
vector<Comparable> bubbleSort(vector<Comparable> vec, unsigned long& reads, unsigned long& allocations) {
    reads = allocations = 0;
    int numPasses = 0;
    int i;
    allocations += 2 * sizeof(int);

    Comparable temp;
    allocations += sizeof(Comparable);

    bool haveSwapped = true;
    allocations += sizeof(bool);

    while (haveSwapped) {
        haveSwapped = false;
        reads += 1;

        for (i = 0; i+1 < vec.size()-numPasses; ++i) {
            reads += 1;

            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i] > vec[i+1]) {

                temp = vec[i];
                reads += 1;

                vec[i] = vec[i+1];
                reads += 1;

                vec[i+1] = temp;
                reads += 1;
                // Update haveSwapped
                haveSwapped = true;
                reads += 1;
            }
            reads += 2; //to account for if statement
        }
        // Update numPasses
        ++numPasses;

        // Uncomment this line if you want to see each iteration
        //printVec(vec);
    }
    return vec;
}

#endif
