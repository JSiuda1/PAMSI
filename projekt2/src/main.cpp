#include <iostream>
#include <ctime>
#include "../inc/MovieCollection.hh"
#include "../inc/mergeSort.hh"
#include "../inc/quickSort.hh"
#include "../inc/bucketSort.hh"


int main(){
  clock_t time;
  std::string path = "../dane.csv";
  unsigned int filtredData;
  unsigned int readedData;
  MovieDataBase mdb(path);
  std::vector<std::string> data;
  std::vector<Movie> movies;
  std::vector<Movie> toSort;
  std::vector<int> inputSize = {1000, 10000, 100000, 1000000};

  if(mdb.openDataBaseFile()==false){
    std::cout << "File bad :C" << std::endl;
    return 1;
  }

  for(int size : inputSize){
    std::cout << std::endl << "******************************" << std::endl << std::endl;
    /*
    time = clock();
    readedData = mdb.getStringDataFromFile(data, size);
    time = clock() - time;
    std::cout << "Wczytano: " << readedData << std::endl;
    std::cout << "Wczytanie danych zajelo: " << (float)time/CLOCKS_PER_SEC << std::endl;
    
    
    time = clock();
    filtredData = mdb.filtrStringData(data, ',', 2);
    time = clock() - time;
    std::cout << "Usunieto " << filtredData << " pozycji" << std::endl;
    std::cout << "Filtrowanie danych zajelo: " << (float)time/CLOCKS_PER_SEC << std::endl;
    


    time = clock();
    mdb.convertStringToMovie(data, movies,',');
    time = clock() - time;
    std::cout << "Konwertowanie zajelo: " << (float)time/CLOCKS_PER_SEC << std::endl;
    


    toSort = movies;  
    time = clock();
    sort::quickSort(toSort, 0, toSort.size() - 1);
    time = clock() - time;
    std::cout << "Quick sort: " << (float)time/CLOCKS_PER_SEC << std::endl;
    toSort = movies;  
    */

    
    int test[] = {6,5,7,4,2,1,3};
    time = clock();
    sort::mergeSort(test, 0 , sizeof(test)/sizeof(test[0]));
    time = clock() - time;
    std::cout << "Merge sort: " << (float)time/CLOCKS_PER_SEC << std::endl;
    
    for(auto var : test){
      std::cout << var << std::endl;
    }
    /*
    toSort = movies;  
    time = clock();
    sort::bucketSort(toSort, 11);
    time = clock() - time;
    std::cout << "Bucket sort: " << (float)time/CLOCKS_PER_SEC << std::endl;
    */

    data.clear();
    movies.clear();
    toSort.clear();

     //std::cout << std::endl << "******************************" << std::endl << std::endl;
  }
  std::cout << std::endl << "******************************" << std::endl << std::endl;
  return 0;
}
