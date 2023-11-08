#include "QuickSort.hpp"
#include <iostream>
#include <random>
#include <chrono>
#define N 10000000ULL

static std::mt19937_64 generator(std::chrono::system_clock::now().time_since_epoch().count());

void TWP(ull arr[], ull m, ull n, ull &begin, ull &end) {
  std::uniform_int_distribution<ull> distribution(m, n);
  ull pivotIndex = distribution(generator);
  ull pivot = arr[pivotIndex];
  begin = m, end = n;
  
  for(ull i = begin + 1 ; i <= end; i++) {
    if(arr[i] < pivot) {
      std::swap(arr[i], arr[begin]);
      begin++;
    }
    else if(arr[i] > pivot) {
      std::swap(arr[i], arr[end]);
      end--; 
      i--;
    }
  }
}

void quickSort(ull arr[], ull m, ull n) {
  if(m>=n || n >= N) {
    return;
  }
  ull begin, end;
  TWP(arr, m, n, begin, end);
  quickSort(arr, m, --begin);
  quickSort(arr, ++end, n);
}
