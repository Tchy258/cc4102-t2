#include "radix/RadixSort.hpp"
#include "quicksort/QuickSort.hpp"
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <sstream>
#include <limits>
#define N 100000000ULL

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
    header << "U \t QuickSort \t RadixSort k=1";
    for (ull k = 2; k <= 64; k++) {
        header << "\t RadixSort k=" << k;
    }
    header << "\n";
    file << header.str();
    file.flush();
    for (ull universeSize = 2; universeSize <= std::numeric_limits<ull>::max() && universeSize != 0; universeSize = universeSize << 1) {
        std::chrono::duration<ull, std::nano> qSortTotal = std::chrono::duration<ull, std::nano>::zero();
        std::vector<std::chrono::duration<ull, std::nano>> rSortTotal(integerLog2(universeSize) + 1,std::chrono::duration<ull, std::nano>::zero());
        std::stringstream line;
        line << universeSize << "\t";
        for (int i = 0; i < 100; i++) {
            ull* array = generateRandomArray(0, universeSize);
            std::chrono::duration<ull, std::nano> elapsed;
            ull* arrayCopy = new ull[N];
            std::memcpy(arrayCopy, array, N * sizeof(ull));
            auto start = std::chrono::high_resolution_clock::now();
            quickSort(arrayCopy, 0, N - 1, N);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            qSortTotal += elapsed;
            delete[] arrayCopy;
            for (ull k = 1; k <= integerLog2(universeSize); k++ ) {
                std::chrono::duration<ull, std::nano> elapsed;
                ull* arrayCopy = new ull[N];
                std::memcpy(arrayCopy, array, N * sizeof(ull));
                auto start = std::chrono::high_resolution_clock::now();
                radixSort(arrayCopy, N, universeSize, k);
                auto end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                rSortTotal[k] += elapsed;
                delete[] arrayCopy;
            }
            delete[] array;
            line << (qSortTotal.count() / 100) << "\t";
            for (ull k = 1; k <= integerLog2(universeSize); k++ ) {
                line << (rSortTotal[k].count() / 100) << "\t";
            }
        }
        line << "\n";
        file << line.str();
        file.flush();
    }
    file.close();
    return 0;
}