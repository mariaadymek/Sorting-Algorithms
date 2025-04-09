#include "sorting-algorithms/bubbleSort.h"
#include "sorting-algorithms/heapSort.h"
#include "sorting-algorithms/insertionSort.h"
#include "sorting-algorithms/mergeSort.h"
#include "sorting-algorithms/quickSort.h"
#include "sorting-algorithms/radixSort.h"
#include "sorting-algorithms/selectionSort.h"
#include "stability-test/contactsList.h"
#include <iomanip>
#include "SpotifyMusic.h"
#include <algorithm>
#include <random>
#include <fstream> // For writing output files
#include <cstdlib> // For system() calls
using namespace std;

void stabilityTest();
void runSortingAlgorithms(const vector<SpotifyMusic>& songs);
void createDataDirectory();
void writeSortingData(const string& algorithm, const vector<pair<int, unsigned long>>& readsData,
                    const vector<pair<int, unsigned long>>& allocationsData);

int main() {
    vector<SpotifyMusic> songs;

    // Create data directory if it doesn't exist
    createDataDirectory();

    // Opens data file and creates vector of data
    if(getDataFromFile(songs)) {
        cout << "Read in data successfully, size of vector: " << songs.size() << endl;
    }

    // Randomizing the vector
    random_device rd;
    mt19937 g(rd());
    shuffle(songs.begin(), songs.end(), g);

    // Run all sorting algorithms
    runSortingAlgorithms(songs);

    // Run stability test
    stabilityTest();

    // Call Python script to generate graphs
    cout << "\nGenerating graphs using Python..." << endl;
    system("python3 graph_generator.py");

    return 0;
}

void createDataDirectory() {
    // Create data directory if it doesn't exist
    if (!filesystem::exists("data")) {
        filesystem::create_directory("data");
        cout << "Created 'data' directory" << endl;
    }
}

void runSortingAlgorithms(const vector<SpotifyMusic>& songs) {
    // Vectors to store data for each algorithm
    vector<pair<int, unsigned long>> bubbleSortReads, bubbleSortAllocations;
    vector<pair<int, unsigned long>> mergeSortReads, mergeSortAllocations;
    vector<pair<int, unsigned long>> heapSortReads, heapSortAllocations;
    vector<pair<int, unsigned long>> quickSortReads, quickSortAllocations;

    for (int size = 100; size <= 1000; size += 100) {
        cout << "\nSorting vector of size " << size << endl;
        vector<SpotifyMusic> currentSubset(songs.begin(), songs.begin() + size);
        unsigned long reads = 0, allocations = 0;

        // Bubble Sort
        cout << "Bubble Sort" << endl;
        bubbleSort(currentSubset, reads, allocations);
        cout << "Reads: " << reads << " Allocations: " << allocations << endl;
        bubbleSortReads.push_back({size, reads});
        bubbleSortAllocations.push_back({size, allocations});
        reads = 0;
        allocations = 0;

        // Merge Sort
        cout << "Merge Sort" << endl;
        mergeSort(currentSubset, reads, allocations);
        cout << "Reads: " << reads << " Allocations: " << allocations << endl;
        mergeSortReads.push_back({size, reads});
        mergeSortAllocations.push_back({size, allocations});
        reads = 0;
        allocations = 0;

        // Heap Sort
        cout << "Heap Sort" << endl;
        heapSort(currentSubset, reads, allocations);
        cout << "Reads: " << reads << " Allocations: " << allocations << endl;
        heapSortReads.push_back({size, reads});
        heapSortAllocations.push_back({size, allocations});
        reads = 0;
        allocations = 0;

        // Quick Sort
        cout << "Quick Sort" << endl;
        quickSortUnstable(currentSubset, reads, allocations);
        cout << "Reads: " << reads << " Allocations: " << allocations << endl;
        quickSortReads.push_back({size, reads});
        quickSortAllocations.push_back({size, allocations});
        reads = 0;
        allocations = 0;
    }

    // Write data to files
    writeSortingData("bubble_sort", bubbleSortReads, bubbleSortAllocations);
    writeSortingData("merge_sort", mergeSortReads, mergeSortAllocations);
    writeSortingData("heap_sort", heapSortReads, heapSortAllocations);
    writeSortingData("quick_sort", quickSortReads, quickSortAllocations);
}

void writeSortingData(const string& algorithm, const vector<pair<int, unsigned long>>& readsData,
                    const vector<pair<int, unsigned long>>& allocationsData) {
    // Write reads data
    string readsFilename = "data/" + algorithm + "_reads.csv";
    ofstream readsFile(readsFilename);

    if (readsFile.is_open()) {
        readsFile << "size,reads\n";
        for (const auto& data : readsData) {
            readsFile << data.first << "," << data.second << "\n";
        }
        readsFile.close();
        cout << "Wrote data to " << readsFilename << endl;
    } else {
        cerr << "Unable to open file: " << readsFilename << endl;
    }

    // Write allocations data
    string allocationsFilename = "data/" + algorithm + "_allocations.csv";
    ofstream allocationsFile(allocationsFilename);

    if (allocationsFile.is_open()) {
        allocationsFile << "size,allocations\n";
        for (const auto& data : allocationsData) {
            allocationsFile << data.first << "," << data.second << "\n";
        }
        allocationsFile.close();
        cout << "Wrote data to " << allocationsFilename << endl;
    } else {
        cerr << "Unable to open file: " << allocationsFilename << endl;
    }
}

void stabilityTest() {
    ContactsList people;
    people.readContactsFromFile("../stability-test/names.csv");
    cout << "People (Default ordering)" << endl;
    people.printList();

    cout << endl << "Bubble Sort" << endl;
    people.sortAndPrint(bubbleSort<contact>);

    cout << endl << "Merge Sort" << endl;
    people.sortAndPrint(mergeSort<contact>);

    cout << endl << "Heap Sort" << endl;
    people.sortAndPrint(heapSort<contact>);

    cout << endl << "Quick Sort" << endl;
    people.sortAndPrint(quickSortUnstable<contact>);
}