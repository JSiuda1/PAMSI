#pragma once

#include <string.h>

#define ALL_ELEMENTS 0

#include "string"
#include "Movie.hh"
#include "FileRead.hh"
#include "stdint.h"

class MovieDataBase{
  File file;

  public:
  MovieDataBase(const std::string & path);
  MovieDataBase(char* path);
  bool openDataBaseFile();
  void closeDataBaseFile();
  unsigned int getStringDataFromFile(std::string *data, unsigned int long elements);
  unsigned int filtrStringData(std::string* data, size_t size, char delimiter, unsigned int numbersOfDelimiter = 2);
  void convertStringToMovie(std::string* _vec, Movie* movies , size_t size, char delimiter);
  bool checkSortCorrectness(Movie* data, size_t size);
  double getAverageRank(Movie *data, size_t size);
  double getMediana(Movie *data, size_t size);
};
