#pragma once

#include "vector"

namespace sort{

template<typename Type>
void merge(Type* array, size_t begin, size_t mid, size_t end){
  size_t leftArrSize = mid - begin + 1;
  size_t rightArrSize = end - mid;
  Type leftArr[leftArrSize];
  Type rightArr[rightArrSize];

  for(size_t i = 0; i < leftArrSize; ++i){
    leftArr[i] = array[begin + i];
  }

  for(size_t j = 0; j < rightArrSize; ++j){
    rightArr[j] = array[mid + 1 + j];
  }
  size_t i = 0, j = 0, k = begin;

  while(i < leftArrSize && j < rightArrSize){
    if(leftArr[i] <= rightArr[j]){
      array[k] = leftArr[i];
      ++i;
    }else{
      array[k] = rightArr[j];
      ++j;
    }
    k++;
  } 

  while(i < leftArrSize){
    array[k] = leftArr[i];
    ++i;
    ++k;
  }

  while(j < rightArrSize){
    array[k] = rightArr[j];
    ++j;
    ++k;
  }
}

template<typename Type>
void mergeSort(Type* array, size_t begin, size_t end)
{
  if (begin >= end)
    return; 
  
  int mid = begin + (end - begin) / 2;
  mergeSort(array, begin, mid);
  mergeSort(array, mid + 1, end);
  merge(array, begin, mid, end);
}


template void merge(Movie*, size_t , size_t , size_t );
template void mergeSort(Movie* , size_t, size_t);
}
