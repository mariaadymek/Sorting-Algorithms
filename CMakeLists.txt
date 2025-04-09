cmake_minimum_required(VERSION 3.15)
project(Project4)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(M3AP
        sorting-algorithms/bubbleSort.h
        sorting-algorithms/heapSort.h
        sorting-algorithms/insertionSort.h
        sorting-algorithms/mergeSort.h
        sorting-algorithms/printVec.h
        sorting-algorithms/quickSort.h
        sorting-algorithms/radixSort.h
        sorting-algorithms/selectionSort.h
        main.cpp
        stability-test/contactsList.h
        SpotifyMusic.cpp)
