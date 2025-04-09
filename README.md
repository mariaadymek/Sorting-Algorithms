# Sorting Algorithm Analysis in C++

## Overview

This project explores and compares the performance of multiple sorting algorithms by sorting a custom dataset of over 1000 objects. In addition to implementing traditional sorting techniques, I instrumented each algorithm to collect detailed performance metrics such as the number of object reads and memory allocations. The final goal was to evaluate algorithm efficiency and stability, particularly on real-world-sized datasets.

## Languages & Tools Used

- **Language**: C++
- **Compiler**: g++ (via terminal)
- **Standard Library**: STL (`<vector>`, `<iostream>`, etc.)
- **Build Tool**: Manual compilation

## Features

- Custom class with all comparison operators overloaded
- Sorting algorithms implemented:
  - Bubble Sort (Stable)
  - Merge Sort (Stable, non-constant auxiliary complexity)
  - Heap Sort (Unstable)
  - Quick Sort (Unstable)
- Tracking:
  - Number of **reads** (accesses of Comparable objects)
  - Number of **allocations** (temporary memory usage)
- Varying input sizes from 100 to 1000 (in increments of 100)
- Stability test function using a predefined contact list

## How It Works

Each sorting algorithm was modified to include logic that:
- **Counts reads** every time a Comparable object is accessed.
- **Counts allocations** using the `sizeof()` operator for temporary variables.

All algorithms receive an identical copy of the original unsorted vector to ensure fair performance comparisons. The program collects read/allocation data across increasing input sizes to visualize scalability.
