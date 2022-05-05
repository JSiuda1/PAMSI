#pragma once

#include "vector"

namespace sort{

template <typename Type>
void swap(Type *a, Type *b){
  Type t = *a;
  *a = *b;
  *b = t;
}

template <typename Type>
int partition(std::vector<Type> & vec, int low, int high){
  //select last element as a pivot
  Type pivot = vec[high];
  //std::vector<Type>::iterator vecIter = vec.begin();
  
  int i = low;

  for(int j = low; j < high; ++j){
    if(vec[j] <= pivot){
      swap(&vec[i], &vec[j]);
      i++;
    }
  }
  //swap the pivot
  swap(&vec[i], &vec[high]);

  return i;
}

template <typename Type>
void quickSort(std::vector<Type> & vec, int low, int high){
  if(low < high){
    //find pivot element
    int pivot = partition(vec, low, high);
    quickSort(vec, low, pivot-1);
    quickSort(vec, pivot+1, high);
  }
}


template void swap(Movie* a, Movie* b);
template int partition(std::vector<Movie> & vec, int low, int high);
template void quickSort(std::vector<Movie> & vec, int low, int high);

}