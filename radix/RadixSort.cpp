#include "RadixSort.hpp"
#include <math.h>
ull integerLog2(ull k) {
    ull result = 0;
    while (k >>= 1) {
        result++;
    }
    return result;

}

void bucketSort(ull* arrayToSort, ull arraySize, ull uSize, ull bitMaskToApply, ull shift) {
    ull* countingArray = (ull*) calloc(uSize + 2, sizeof(ull));
    for (ull i = 0; i < arraySize; i++) {
        ull value = ((arrayToSort[i] >> shift) & bitMaskToApply ) + 1;
        countingArray[value] += 1;
    }
    countingArray[0] = 1;
    for (ull i = 1; i < uSize + 1; i++) {
        countingArray[i] += countingArray[i-1];
    }
    ull* bucketArray = (ull*) calloc(arraySize, sizeof(ull));
    for (ull i = 0; i < arraySize; i++) {
        ull position = (arrayToSort[i] >> shift) & bitMaskToApply;
        bucketArray[countingArray[position] - 1] = arrayToSort[i];
        countingArray[position]++;
    }
    std::free(countingArray);
    std::memcpy(arrayToSort,bucketArray, arraySize * sizeof(ull));
    std::free(bucketArray);
}

void radixSort(ull* arrayToSort, ull arraySize, ull uSize, ull kBits) {
    ull bitMask = (1 << kBits) - 1;
    ull radixUSize = 1 << kBits;
    ull maxShift = integerLog2(uSize);
    for (ull shift = 0; shift <= maxShift; shift+= kBits) {
        bucketSort(arrayToSort, arraySize,radixUSize, bitMask, shift);
    }
}
