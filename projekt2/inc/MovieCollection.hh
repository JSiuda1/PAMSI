#pragma once

#define ALL_ELEMENTS 0

#include "string"
#include "vector"
#include "Movie.hh"
#include "FileRead.hh"
#include <iostream>

class MovieDataBase{
  File file;
  std::vector<Movie> collection;
  
  public:
  MovieDataBase(const std::string & path);
  MovieDataBase(char* path);
  bool openDataBaseFile();
  void closeDataBaseFile();
  void getMoviesFromFile(uint elements = ALL_ELEMENTS, char delimiter = ';');
  std::vector<Movie> getMovieCollection() const;

  private:
  void getDataFromFile(std::vector<std::string> & data, uint long elements);
  void filtrReadedData(std::vector<std::string> & data, char delimiter, uint numbersOfDelimiter = 2);
  Movie convertStringToMovie(const std::string & _str, char delimiter);
};

std::ostream & operator<<(std::ostream & strm, const MovieDataBase & arg);