#include "RadixSort.hpp"

void bucketSort(ull* arrayToSort, ull arraySize, ull uSize, ull bitMaskToApply, ull reverseShift) {
    ull* countingArray = (ull*) calloc(uSize + 2, sizeof(ull));
    for (ull i = 0; i < arraySize; i++) {
        ull value = ((arrayToSort[i] & bitMaskToApply) >> reverseShift) + 1;
        countingArray[value] += 1;
    }
    countingArray[0] = 1;
    for (ull i = 1; i < uSize + 1; i++) {
        countingArray[i] += countingArray[i-1];
    }
    ull* bucketArray = (ull*) calloc(arraySize, sizeof(ull));
    for (ull i = 0; i < arraySize; i++) {
        ull position = (arrayToSort[i] & bitMaskToApply) >> reverseShift;
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
    for (ull shift = 0; bitMask != 0; shift = shift + kBits) {
        bucketSort(arrayToSort, arraySize,radixUSize, bitMask, shift);
        bitMask = bitMask << kBits;
    }
}
