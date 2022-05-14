#include <iostream>
#include <ctime>
#include "../inc/MovieCollection.hh"
#include "../inc/mergeSort.hh"
#include "../inc/quickSort.hh"
#include "../inc/bucketSort.hh"
#include "../inc/introspectiveSort.hh"
#include <sys/resource.h>

int main(){
  clock_t time;
  std::string path = "../dane.csv";
  unsigned int filtredData;
  unsigned int readedData;
  MovieDataBase mdb(path);
  std::string* data;
  Movie *movies;
  size_t newSize = 0;
  Movie *toSort;
  std::vector<size_t> inputSize = {100, 1000, 10000, 100000, 500000, 1000000};


  const rlim_t kStackSize = 1024* 1024 * 1024;   // min stack size = 1 GB
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


  if(mdb.openDataBaseFile()==false){
    std::cout << "File bad :C" << std::endl;
    return 1;
  }

  for(size_t & size : inputSize){
    //std::cout << std::endl << "******************************" << std::endl << std::endl;
    std::cout << "Rozmiar: " << size << std::endl;
  for(int i=0; i < 100; i++){

    data = new std::string[size];

    time = clock();
    readedData = mdb.getStringDataFromFile(data, size);
    time = clock() - time;
    //std::cout << "Wczytano: " << readedData << std::endl;
    //std::cout << "Wczytanie danych zajelo: " << (float)time/CLOCKS_PER_SEC << std::endl;
  

    
    time = clock();
    filtredData = mdb.filtrStringData(data, size,',', 2);
    time = clock() - time;
    //std::cout << "Usunieto " << filtredData << " pozycji" << std::endl;
    //std::cout << "Filtrowanie danych zajelo: " << (float)time/CLOCKS_PER_SEC << std::endl;
    
    
    

    newSize = size - filtredData;
    movies = new Movie[newSize];

    time = clock();
    mdb.convertStringToMovie(data, movies, newSize, ',');
    time = clock() - time;
    //std::cout << "Konwertowanie zajelo: " << (float)time/CLOCKS_PER_SEC << std::endl;
    
    toSort = new Movie[newSize];    

    std::copy(movies, movies + newSize, toSort);
   
    std::cout<<i << ";";
    time = clock();
    sort::mergeSort(toSort, 0, newSize - 1);
    time = clock() - time;
    std::cout << (float)time/CLOCKS_PER_SEC << ";";
    
    std::copy(movies, movies + newSize, toSort);

    time = clock();
    sort::quickSort(toSort, 0, newSize - 1);
    time = clock() - time;
    std::cout << (float)time/CLOCKS_PER_SEC << ";";

    std::copy(movies, movies + newSize, toSort);

    time = clock();
    sort::bucketSortInsertSort(toSort, newSize, 11);
    time = clock() - time;
    std::cout << (float)time/CLOCKS_PER_SEC << ";";

    std::copy(movies, movies + newSize, toSort);

    time = clock();
    sort::bucketSortInsertSort(toSort, newSize, 11);
    time = clock() - time;
    std::cout << (float)time/CLOCKS_PER_SEC << ";"<< std::endl;
    
    delete[] toSort;
    delete[] data;
    delete[] movies;
  }
  }
  return 0;
}
