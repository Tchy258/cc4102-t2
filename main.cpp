#include "radix/RadixSort.hpp"
#include "quicksort/QuickSort.hpp"
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <sstream>
#include <limits>
#define N 10000000ULL

ull* generateRandomArray(ull seed, ull universeSize) {
    ull arraySize = N;
    ull* array = new ull[arraySize];
    std::mt19937_64 generator;
    if (seed != 0) {
        generator = std::mt19937_64(seed);
    } else {
        generator = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
    }
    std::uniform_int_distribution<ull> distribution(1, universeSize);
    for (ull i = 0; i < arraySize; i++) {
        array[i] = distribution(generator);
    }
    return array;

}

int main(int argc, char** argv) {
    ull seed = 0;
    if (argc == 2) {
        seed = std::stoull(argv[1]);
    }
    std::ofstream file;
    file.open("results.csv");
    std::stringstream header;
    header << "U,QuickSort,RadixSort k=1";
    for (ull k = 2; k <= integerLog2(N); k++) {
        header << ",RadixSort k=" << k;
    }
    header << "\n";
    file << header.str();
    file.flush();
    ull* arrayCopy = new ull[N];
    for (ull universeSize = 2; universeSize <= std::numeric_limits<ull>::max(); universeSize = universeSize << 1 == 0 ? std::numeric_limits<ull>::max() : universeSize << 1) {
        ull kLimit = std::min(integerLog2(universeSize), integerLog2(N));
        std::chrono::duration<ull, std::micro> qSortTotal = std::chrono::duration<ull, std::micro>::zero();
        std::vector<std::chrono::duration<ull, std::micro>> rSortTotal(kLimit + 1,std::chrono::duration<ull, std::micro>::zero());
        std::stringstream line;
        line << universeSize << ",";
        for (int i = 0; i < 100; i++) {
            ull* array = generateRandomArray(seed, universeSize);
            std::chrono::duration<ull, std::micro> elapsed;
            std::memcpy(arrayCopy, array, N * sizeof(ull));
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
            quickSort(arrayCopy, 0, N - 1);
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
            elapsed = end - start;
            qSortTotal += elapsed;
            for (ull k = 1; k <= kLimit; k++ ) {
                std::chrono::duration<ull, std::micro> elapsed;
                std::memcpy(arrayCopy, array, N * sizeof(ull));
                auto start = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
                radixSort(arrayCopy, N, universeSize, k);
                auto end = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
                elapsed = end - start;
                rSortTotal[k] += elapsed;
            }
            delete[] array;
        }
        line << (qSortTotal.count() / 100) << ",";
        for (ull k = 1; k <= kLimit; k++ ) {
            line << (rSortTotal[k].count() / 100) << ",";
        }
        line << "\n";
        file << line.str();
        file.flush();
        if (universeSize == std::numeric_limits<ull>::max()) {
            break;
        }
    }
    delete[] arrayCopy;
    file.close();
    return 0;
}
