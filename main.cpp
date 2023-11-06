#include "radix/RadixSort.hpp"
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <sstream>

ull integerLog2(ull k) {
    ull result = 0;
    while (k >>= 1) {
        result++;
    }
    return result;

}

ull* generateRandomArray(ull seed, ull universeSize) {
    ull arraySize = 100000000LL;
    ull* array = new ull[arraySize];
    std::mt19937_64 generator;
    if (seed != 0) {
        generator = std::mt19937_64(seed);
    } else {
        generator = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
    }
    std::uniform_int_distribution<ull> distribution(0, universeSize);
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
    std::stringstream line;
    line << "U \t RadixSort \t QuickSort\n";
    for (ull universeSize = 2; universeSize <= (ull) (-1LL); universeSize = universeSize << 1) {
        ull* array = generateRandomArray(0, universeSize);
        // Aquí hay que poner el quicksort y el radix con k = 1
        for (ull k = 2; k <= integerLog2(universeSize); k++ ) {
            std::chrono::duration<double> elapsed;
            ull* arrayCopy = new ull[100000000LL];
            std::memcpy(arrayCopy, array, 100000000LL * sizeof(ull));
            auto start = std::chrono::high_resolution_clock::now();
            radixSort(arrayCopy, 100000000LL, universeSize, k);
            auto end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            line << universeSize << "\t" << elapsed.count() << "\t -\n";
            delete[] arrayCopy;
        }
        delete[] array;
    }
    file << line.str();
    file.close();
    return 0;
}