#pragma once

namespace sort{

template <typename Type>
void swap(Type *a, Type *b){
  Type t = *a;
  *a = *b;
  *b = t;
}

template <typename Type>
void medianThree(Type *arr, int low, int mid, int high) {
  if(arr[mid] < arr[low]){
    swap(&arr[mid], &arr[low]);
  }else if(arr[high] < arr[low]){
    swap(&arr[high], &arr[low]);
  }else if(arr[mid] < arr[high]){
    swap(&arr[mid], &arr[high]);
  }
}

template <typename Type>
int partition(Type* arr, int low, int high){
  Type pivot = arr[high];
  
  int i = low;

  for(int j = low; j < high; ++j){
    if(arr[j] <= pivot){
      swap(&arr[i], &arr[j]);
      i++;
    }
  }
  //swap the pivot
  swap(&arr[i], &arr[high]);

  return i;
}


template <typename Type>
void quickSort(Type* arr, int low, int high){
  if(low < high){
    //find pivot element
    int pivot = partition(arr, low, high);
    quickSort(arr, low, pivot-1);
    quickSort(arr, pivot+1, high);
  }
}
template <typename Type>
int partitionMediana(Type* arr, int low, int high){
  medianThree(arr, low, (low+high)/2, high);
  Type pivot = arr[high];
  
  int i = low;

  for(int j = low; j < high; ++j){
    if(arr[j] <= pivot){
      swap(&arr[i], &arr[j]);
      i++;
    }
  }
  //swap the pivot
  swap(&arr[i], &arr[high]);

  return i;
}

template <typename Type>
void quickSortMediana(Type* arr, int low, int high){
  if(low < high){
    //find pivot element
    int pivot = partitionMediana(arr, low, high);
    quickSort(arr, low, pivot-1);
    quickSort(arr, pivot+1, high);
  }
}



template void swap(Movie* a, Movie* b);
template int partition(Movie* arr, int low, int high);
template void quickSort(Movie* arr, int low, int high);
template void medianThree(Movie*, int, int, int);
template int partitionMediana(Movie* arr, int low, int high);
template void quickSortMediana(Movie* arr, int low, int high);

}