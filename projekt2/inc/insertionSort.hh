#pragma once

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

template void insertionSort(Movie*, size_t, size_t);

}