#pragma once

#include <cmath>
#include "bucketSort.hh"

namespace sort{

template <typename Type>
void swapValue(Type *a, Type *b){
  Type t = *a;
  *a = *b;
  *b = t;
}

int medianaOfThree(size_t a, size_t b, size_t c){
  if ((a > b) ^ (a > c)) 
    return a;
  else if ((b < a) ^ (b < c)) 
    return b;
  else
    return c;
}

template <typename Type>
void introSort(Type *array, size_t begin, size_t end, size_t stackDepth){
  if((end - begin) < 16){
    insertionSort(array, begin, end);
    return;
  }

  if(stackDepth == 0){
    //heap sort
    std::cout << "heap" << std::endl;
    return;
  }

  int pivot = medianaOfThree(begin, (begin+ end)/2, end);
  swapValue(&array[pivot], &array[end-1]);
  introSort(array, begin, pivot - 1, stackDepth - 1);
  introSort(array, pivot + 1, end, stackDepth - 1);
}

template <typename Type>
void introspectiveSort(Type *array, size_t size){
  size_t depthLimit = 2* log(size);
  
  introSort(array, 0, size, depthLimit);
}




template void swapValue(int *a, int *b);
template void introspectiveSort(int *array, size_t size);
template void introSort(int *array, size_t begin, size_t end, size_t stackDepth);

}