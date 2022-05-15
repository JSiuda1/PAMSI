#pragma once

#include <vector>
#include <array>
#include "quickSort.hh"

namespace sort{

template <typename Type>
void insertionSort(Type* vec, size_t begin, size_t end){
  Type key;
  int j = begin;
  
  for(int step = begin + 1; step < end - begin; ++step){
    key = vec[step];
    j = step - 1;

    while(key < vec[j] && j >= 0){
      vec[j+1] = vec[j];
      --j;
    }
    vec[j+1] = key;
  }
}

/**
 * @b11rief bucketSort algorithm with quicksort
 * 
 * @tparam Type type of sorted data
 * @param vec data input
 * @param bucketNumber should be equal with range of elements
 */

template <typename Type>
void bucketSort(Type* vec, const size_t size, const size_t bucketNumber, const size_t threshold = 50){
  Type buckets[bucketNumber][size];
  int bucketElements[bucketNumber];
  Type elem;
  int elemToIntVal;

  //initialize buckets
  for(size_t i =0; i < bucketNumber; ++i){
    bucketElements[i] = 0;
  }

  for(size_t i = 0; i < size; ++i){
    elem = vec[i];
    elemToIntVal = static_cast<int>(elem);

    if(elemToIntVal > 0 && elemToIntVal < bucketNumber){
      buckets[elemToIntVal][bucketElements[elemToIntVal]] = elem;
      bucketElements[elemToIntVal]++;
    }else{
      //exception
    }
  }

  size_t k = 0;
  for(size_t i = 0; i < bucketNumber; ++i){
    if(bucketElements[i] > threshold){
      mergeSort(buckets[i], 0, bucketElements[i] - 1);
    }else{
      insertionSort(buckets[i], 0, bucketElements[i]);
    }
    
    
    for(size_t j = 0; j < bucketElements[i]; ++j){
      vec[k+j] = buckets[i][j];
    }
    k += bucketElements[i];
  }
}

  template void insertionSort(Movie*, size_t, size_t);
  template void bucketSort(Movie*, const size_t, const size_t, const size_t);
}