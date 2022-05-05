#pragma once

#define ALL_ELEMENTS 0

#include "string"
#include "vector"
#include "Movie.hh"
#include "FileRead.hh"
#include <iostream>
#include "stdint.h"
#include "mergeSort.hh"
#include "quickSort.hh"
#include "bucketSort.hh"

class MovieDataBase{
  File file;
  std::vector<Movie> collection;
  
  public:
  MovieDataBase(const std::string & path);
  MovieDataBase(char* path);
  bool openDataBaseFile();
  void closeDataBaseFile();
  unsigned int getMoviesFromFile(unsigned int elements = ALL_ELEMENTS, char delimiter = ';');
  std::vector<Movie> getMovieCollection() const;
  void mergeSort();
  void quickSort();
  void bucketSort(const size_t & bucketNumber = 11);
  void clearImportedMovies();

  private:
  void getDataFromFile(std::vector<std::string> & data, unsigned int long elements);
  unsigned int filtrReadedData(std::vector<std::string> & data, char delimiter, unsigned int numbersOfDelimiter = 2);
  Movie convertStringToMovie(const std::string & _str, char delimiter);
};

std::ostream & operator<<(std::ostream & strm, const MovieDataBase & arg);