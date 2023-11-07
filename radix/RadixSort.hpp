#ifndef RADIXSORT_HPP
#define RADIXSORT_HPP
#include<cstdlib>
#include<cstring>
typedef unsigned long long ull;

void radixSort(ull* arrayToSort, ull arraySize, ull uSize, ull kBits);
void bucketSort(ull* arrayToSort, ull arraySize, ull uSize, ull bitMaskToApply, ull reverseShift);
ull integerLog2(ull k);

#endif // RADIXSORT_HPP