#pragma once

#include "vector"

namespace sort{

template<typename Type>
void merge(Type array[], size_t left, size_t mid, size_t right){
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
  
    // Create temp arrays
    Type leftArray[subArrayOne];
    Type rightArray[subArrayTwo];
  
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
  
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

template<typename Type>
void mergeSort(Type array[], int begin, int end)
{
    if (begin >= end)
        return; // Returns recursively
  
    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
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
template void mergeSort(Movie array[], int begin, int end);
template void mergeSort(int array[], int begin, int end);
//template void mergeSort(Movie* arr, size_t begin, size_t end);
template void merge(int* arr, size_t begin, size_t mid, size_t end);
//template void mergeSort(int* arr, size_t begin, size_t end);
}
