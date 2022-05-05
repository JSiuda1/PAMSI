#pragma once

#include "vector"

namespace sort{

template<typename Type>
void merge(std::vector<Type> & vec, size_t begin, size_t mid, size_t end){
  std::vector<Type> result = vec;
  Type temp;

  int i = begin;
  int j = mid;


  for (int k = begin; k < end; k++) {
      if (i < mid && (j >= end || vec[i] <= vec[j])) {
        result[k] = vec[i];
        i = i + 1;
      } else {
        result[k] = vec[j];
        j = j + 1;
    }
  }
  vec = result;
}

template<typename Type>
void mergeSort(std::vector<Type> & vec, size_t begin, size_t end){
  size_t mid = 0;

  if(end - begin <= 1){ //splited to 1 element vec
    return;
  }

  mid = (begin + end) / 2;

  mergeSort(vec, begin, mid); //sort left part
  mergeSort(vec, mid, end); //sort right part
  merge(vec, begin, mid, end);
}

template void mergeSort(std::vector<int> & vec, size_t begin, size_t end);
template void merge(std::vector<int> & vec, size_t begin, size_t mid, size_t end);
template void mergeSort(std::vector<Movie> & vec, size_t begin, size_t end);
template void merge(std::vector<Movie> & vec, size_t begin, size_t mid, size_t end);
}
