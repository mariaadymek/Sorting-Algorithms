#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <cmath>
#include "printVec.h"

// Note: Not a template function
vector<int> radixSort(vector<int> vec, int numDigits, unsigned long& reads, unsigned long& allocations) {
    reads = allocations = 0;
    int iteration, i, digit, bucket, item;
    vector<vector<int>> buckets(10);
    for (iteration = 0; iteration < numDigits; ++iteration) {
        // Copy everything from vec into buckets
        for (i = 0; i < vec.size(); ++i) {
            digit = (vec[i] / int(pow(10, iteration)) % 10);
            buckets[digit].push_back(vec[i]);
        }
        // Copy everything from buckets back into vec
        i = 0;
        for (bucket = 0; bucket < buckets.size(); ++bucket) {
            for (item = 0; item < buckets[bucket].size(); ++item) {
                vec[i] = buckets[bucket][item];
                ++i;
            }
            buckets[bucket].clear();
        }

        // Uncomment this line if you want to see each iteration
        //printVec(vec);
    }
    return vec;
}

#endif
