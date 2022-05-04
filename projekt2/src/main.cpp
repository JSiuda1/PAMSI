#include <iostream>
#include "../inc/MovieCollection.hh"
#include "../inc/mergeSort.hh"
#include "../inc/quickSort.hh"

int main(){
  std::string path = "../dane.csv";
  
  /*
  std::vector<int> test = {12,23,4,5,6,7,19,123,54,21,1};

  quickSort(test, 0, test.size() - 1);

  for(auto var : test){
    std::cout << var << "\t";
  }
  std::cout << "\n";
  
  mergeSort(test,0,test.size());
  

  */
  MovieDataBase mdb(path);
  
  if(mdb.openDataBaseFile()==false){
    std::cout << "File bad :C" << std::endl;
    return 1;
  }
  mdb.getMoviesFromFile(100000, ',');

  std::vector<Movie> test = mdb.getMovieCollection();

  for(auto var : test){
    std::cout << var << std::endl;
  }

  std::cout << "\n\n\n";


  quickSort(test, 0, test.size()-1);

  
  for(auto var : test){
    std::cout<< var << std::endl;
  }
  return 0;
}
