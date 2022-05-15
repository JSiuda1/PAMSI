#include <iostream>
#include <ctime>
#include "../inc/MovieCollection.hh"
#include "../inc/mergeSort.hh"
#include "../inc/quickSort.hh"
#include "../inc/bucketSort.hh"
#include <sys/resource.h>
#include <numeric>
#include <vector>

#define SORT_REPEAT 5

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

  void showResults(){
    //std::cout << "Wczytano danych: " << readedData << std::endl;
    //std::cout << "Czas wczytywania danych z pliku: " << readTime << std::endl;
    //std::cout << "Ilość odflitorwanych danych: " << filtredData << std::endl;
    //std::cout << "Czas filtorwania: " << filtrTime << std::endl;
    //std::cout << "Czas konwertowania: " << convertTime << std::endl;
    
    std::cout << readedData << ";";
    std::cout << getAverage(mergeTime) << ";";
    std::cout << getAverage(quickTime) << ";";
    std::cout << getAverage(quickMedianTime) << ";";
    std::cout << getAverage(bucketTime) << ";";

    std::cout << "\n";
  }
};

int main(){
  clock_t time;
  std::string path = "../dane.csv";
  MovieDataBase mdb(path);
  std::string* data;
  Movie *movies;
  size_t newSize = 0;
  Movie *toSort;
  std::vector<size_t> inputSize = {10000, 100000, 500000, 1000000, 10000000};
  /*
  for(int i=1, k = 10000; k < 1000000; ++i){
    inputSize .push_back(k);
    k = 10000 * i;
  }*/


  //change stack size to 512 mb
  const rlim_t kStackSize = 512* 1024 * 1024;
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0){
    if (rl.rlim_cur < kStackSize){
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0){
        fprintf(stderr, "setrlimit returned result = %d\n", result);
      }
    }
  }

  //open data base file
  if(mdb.openDataBaseFile()==false){  
    std::cout << "File bad :C" << std::endl;
    return 1;
  }

  for(size_t & size : inputSize){
    DataFromTest dft;
    dft.sortRepeat = SORT_REPEAT;
    data = new std::string[size];

    //read data from file
    time = clock();
    dft.readedData = mdb.getStringDataFromFile(data, size);
    time = clock() - time;
    dft.readTime = (float)time/CLOCKS_PER_SEC;
    
    //filtr readed data
    time = clock();
    dft.filtredData = mdb.filtrStringData(data, dft.readedData,',', 2);
    time = clock() - time;
    dft.filtrTime = (float)time/CLOCKS_PER_SEC;  

    //create array with filtred data and convert to movie
    newSize = dft.readedData - dft.filtredData;
    movies = new Movie[newSize];
    time = clock();
    mdb.convertStringToMovie(data, movies, newSize, ',');
    time = clock() - time;
    dft.convertTime = (float)time/CLOCKS_PER_SEC;

    

    for(int i=0; i < dft.sortRepeat; i++){
      //array with items to sort  
      toSort = new Movie[newSize];    

      std::copy(movies, movies + newSize, toSort);

    
      time = clock();
      sort::mergeSort(toSort, 0, newSize - 1);
      time = clock() - time;
      dft.mergeTime.push_back((float)time/CLOCKS_PER_SEC);
      dft.correctnes.push_back(mdb.checkSortCorrectness(toSort, newSize));
      dft.average.push_back(mdb.getAverageRank(toSort, newSize));
      dft.mediana.push_back(mdb.getMediana(toSort, newSize));
      
      std::copy(movies, movies + newSize, toSort);

      time = clock();
      sort::quickSort(toSort, 0, newSize - 1);
      time = clock() - time;
      dft.quickTime.push_back((float)time/CLOCKS_PER_SEC);
      dft.correctnes.push_back(mdb.checkSortCorrectness(toSort, newSize));
      dft.average.push_back(mdb.getAverageRank(toSort, newSize));
      dft.mediana.push_back(mdb.getMediana(toSort, newSize));

      std::copy(movies, movies + newSize, toSort);


      time = clock();
      sort::quickSortMediana(toSort, 0, newSize - 1);
      time = clock() - time;
      dft.quickMedianTime.push_back((float)time/CLOCKS_PER_SEC);
      dft.correctnes.push_back(mdb.checkSortCorrectness(toSort, newSize));
      dft.average.push_back(mdb.getAverageRank(toSort, newSize));
      dft.mediana.push_back(mdb.getMediana(toSort, newSize));

      std::copy(movies, movies + newSize, toSort);

      time = clock();
      sort::bucketSort(toSort, newSize, 11, 10001);
      time = clock() - time;

      dft.bucketTime.push_back((float)time/CLOCKS_PER_SEC);
      dft.correctnes.push_back(mdb.checkSortCorrectness(toSort, newSize));
      dft.average.push_back(mdb.getAverageRank(toSort, newSize));
      dft.mediana.push_back(mdb.getMediana(toSort, newSize));


      delete[] toSort;
    }
    dft.showResults();
    
    delete[] data;
    delete[] movies;
  }
  return 0;
}
