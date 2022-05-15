
#pragma once

#include <vector>

float average(std::vector<float> vec){
  float result;
  for(float var : vec)
    result += var;
  return result/vec.size();
}

struct DataFromTest{
  size_t inputSize;
  size_t sortRepeat;
  unsigned int filtredData;
  unsigned int readedData;
  float readTime;
  float filtrTime;
  float convertTime;
  std::vector<double> mediana;
  std::vector<double> average;
  std::vector<bool> correctnes; 
  std::vector<float> mergeTime;
  std::vector<float> quickTime;
  std::vector<float> bucketTime;
  std::vector<float> quickMedianTime;

  float getAverage(std::vector<float> vec){
    float result;
    
    for(float var : vec){
      result += var;
    }
    
    return result/vec.size();
  }

  void showResults(bool readableData = false){
    if(readableData){
      std::cout << "Wczytano danych: " << readedData << std::endl;
      std::cout << "Czas wczytywania danych z pliku: " << readTime << std::endl;
      std::cout << "Ilość odflitorwanych danych: " << filtredData << std::endl;
      std::cout << "Czas filtorwania: " << filtrTime << std::endl;
      std::cout << "Czas konwertowania: " << convertTime << std::endl;

      std::cout << "Merge sort: " << getAverage(mergeTime) << std::endl;
      std::cout << "Quick sort: " << getAverage(quickTime) << std::endl;
      std::cout << "QuickMedian sort: " << getAverage(quickMedianTime) << std::endl;
      std::cout << "Bucket sort: " << getAverage(bucketTime) << std::endl;
    
    }else{
      std::cout << readedData << ";";
      std::cout << getAverage(mergeTime) << ";";
      std::cout << getAverage(quickTime) << ";";
      std::cout << getAverage(quickMedianTime) << ";";
      std::cout << getAverage(bucketTime) << ";";
    }

    std::cout << "\n";
  }
};