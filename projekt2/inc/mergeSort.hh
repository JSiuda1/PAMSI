#pragma once

#include "vector"

namespace sort{

template<typename Type>
void merge(Type * arr, size_t begin, size_t mid, size_t end){
  Type tempArr[end];
  int i = begin;
  int j = mid;

  for (int k = begin; k < end; k++) {
      if (i < mid && (j >= end || arr[i] <= arr[j])) {
        tempArr[k] = arr[i];
        ++i;
      } else {
        tempArr[k] = arr[j];
        ++j;
    }
  }

  //replace array elements with sorted one
  for(int k = begin; k < end; k++){
    arr[k] = tempArr[k - begin];
  }
}

template<typename Type>
void mergeSort(Type* arr, size_t begin, size_t end){
  size_t mid = 0;

  if(end - begin <= 1){ //splited to 1 element vec
    return;
  }

  mid = (begin + end) / 2;

  mergeSort(arr, begin, mid); //sort left part
  mergeSort(arr, mid + 1, end); //sort right part
  merge(arr, begin, mid, end);
}

/*
template<typename Type>
void merge(std::vector<Type> & vec, size_t begin, size_t mid, size_t end){
  std::vector<Type> temp;
  int i = begin;
  int j = mid;

  for (int k = begin; k < end; k++) {
      if (i < mid && (j >= end || vec[i] <= vec[j])) {
        temp.push_back(vec[i]);
        ++i;
      } else {
        temp.push_back(vec[j]);
        ++j;
    }
  }
  vec.erase(vec.begin() + begin, vec.begin() + end);
  vec.insert(vec.begin()  + begin, temp.begin(), temp.end());
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
}*/

//template void mergeSort(std::vector<Movie> & vec, size_t begin, size_t end);
//template void merge(std::vector<Movie> & vec, size_t begin, size_t mid, size_t end);

template void merge(Movie* arr, size_t begin, size_t mid, size_t end);
template void mergeSort(Movie* arr, size_t begin, size_t end);
template void merge(int* arr, size_t begin, size_t mid, size_t end);
template void mergeSort(int* arr, size_t begin, size_t end);
}
