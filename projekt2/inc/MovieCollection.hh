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

  public:
  MovieDataBase(const std::string & path);
  MovieDataBase(char* path);
  bool openDataBaseFile();
  void closeDataBaseFile();
  unsigned int getStringDataFromFile(std::vector<std::string> & data, unsigned int long elements);
  unsigned int filtrStringData(std::vector<std::string> & data, char delimiter, unsigned int numbersOfDelimiter = 2);
  void convertStringToMovie(const std::vector<std::string> & _vec, std::vector<Movie> & movies ,char delimiter);
  
  
};

//std::ostream & operator<<(std::o  