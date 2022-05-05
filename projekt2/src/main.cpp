#include <iostream>
#include "../inc/MovieCollection.hh"
#include "../inc/mergeSort.hh"
#include "../inc/quickSort.hh"
#include "../inc/bucketSort.hh"

int main(){
  std::string path = "../dane.csv";
  unsigned int filtredData;
  MovieDataBase mdb(path);
  
  
  if(mdb.openDataBaseFile()==false){
    std::cout << "File bad :C" << std::endl;
    return 1;
  }
  filtredData = mdb.getMoviesFromFile(1000, ',');
  std::cout << "Usunieto " << filtredData << " pozycji" << std::endl;

  mdb.quickSort();

  mdb.bucketSort();

  return 0;
}
