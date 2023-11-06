#include "QuickSort.hpp"
#include <iostream>
#include <random>
#include <chrono>

ull partition(ull arr[], ull start, ull end) {
    
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<ull> distribution(start, end);
    ull pivotPosition = distribution(generator);
    ull pivot = arr[pivotPosition];
 
    ull count = 0;
    for (ull i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    ull pivotIndex = start + count;
    std::swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    ull i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            std::swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(ull arr[], ull start, ull end, ull arraySize) {
 
    // base case
    if (start >= end || end >= arraySize)
        return;
 
    // partitioning the array
    ull p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1, arraySize);
 
    // Sorting the right part
    quickSort(arr, p + 1, end, arraySize);
}