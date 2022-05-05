#pragma once

#include <vector>
#include <array>
#include "quickSort.hh"

namespace sort{

/**
 * @brief bucketSort algorithm with quicksort
 * 
 * @tparam Type type of sorted data
 * @param vec data input
 * @param bucketNumber should be equal with range of elements
 */
template <typename Type>
void bucketSort(std::vector<Type> & vec, const size_t bucketNumber){
  std::vector<Type> buckets[bucketNumber];
  Type elem;
  int elemToIntVal;
  //fill the buckets
  for(size_t i = 0; i < vec.size(); ++i){
    elem = vec[i];
    elemToIntVal = static_cast<int>(elem);

    if(elemToIntVal > 0 && elemToIntVal < bucketNumber){
      buckets[elemToIntVal].push_back(elem);
    }else{
      throw std::out_of_range("Value out of bucket range");
    }
  }

  //sort each bucket
  for(std::vector<Type> & var : buckets){
    quickSort(var, 0, var.size() - 1);
  }

  //put bucket together
  vec.clear();
  for(std::vector<Type> var : buckets){
    vec.insert(vec.end(), var.begin(), var.end());
  }
}

template void bucketSort(std::vector<Movie> & vec, const size_t bucketNumber);
}