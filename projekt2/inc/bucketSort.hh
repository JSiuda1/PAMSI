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
struct Bucket{
  size_t count;
  Type* values;
};


template <typename Type>
void bucketSortInsertSort(Type* vec, size_t size, const size_t bucketNumber){
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
    insertionSort(buckets[i], 0, bucketElements[i]);
    //quickSort(buckets[i], 0, bucketElements[i] - 1);
    
    for(size_t j = 0; j < bucketElements[i]; ++j){
      vec[k+j] = buckets[i][j];
    }
    k += bucketElements[i];
  }
}

template <typename Type>
void bucketSortMergeSort(Type* vec, size_t size, const size_t bucketNumber){
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
    //insertionSort(buckets[i], 0, bucketElements[i]);
    //quickSort(buckets[i], 0, bucketElements[i] - 1);
    mergeSort(buckets[i], 0, bucketElements[i] - 1);

    for(size_t j = 0; j < bucketElements[i]; ++j){
      vec[k+j] = buckets[i][j];
    }
    k += bucketElements[i];
  }
}



/*
template <typename Type>
void bucketSort(Type * vec, size_t size, const size_t bucketNumber){
  std::vector<Type> buckets[bucketNumber]; 
  Type elem;
  int elemToIntVal;
  //fill the buckets
  for(size_t i = 0; i < size; ++i){
    elem = vec[i];
    elemToIntVal = static_cast<int>(elem);

    if(elemToIntVal > 0 && elemToIntVal < bucketNumber){
      buckets[elemToIntVal].push_back(elem);
    }else{
      throw std::out_of_range("Value out of bucket range");
    }
  }

  //convert vector to arrays
  Type** tempArr = new Type*[bucketNumber];

  
  //creaate and initializes 
  for(int i = 0; i < bucketNumber; ++i){
    tempArr[i] = new Type[buckets[i].size()];
    for(int j =0; j < buckets[i].size(); j++){
      tempArr[i][j] = buckets[i][j];
    }
  }

  //sort each bucket
  for(int i = 0; i < bucketNumber; ++i){
    //quickSort(var, 0, var.size() - 1);
    insertionSort(tempArr[i], buckets[i].size());
  }

  //put bucket together
  for(int i = 0; i < bucketNumber; ++i){
    var
  }
}
*/

  template struct Bucket<Movie>;
  template void insertionSort(Movie*, size_t, size_t);
  template void bucketSortInsertSort(Movie*, size_t, const size_t );
  template void bucketSortMergeSort(Movie*, size_t, const size_t );
  template struct Bucket<int>;
  template void insertionSort(int *, size_t, size_t );
  template void bucketSortInsertSort(int* vec, size_t size, const size_t bucketNumber);
  template void bucketSortMergeSort(int* vec, size_t size, const size_t bucketNumber);
}