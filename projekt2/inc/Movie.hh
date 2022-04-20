#pragma once

#include <iostream>

class Movie{
  std::string title;
  uint rank;

  public:
  Movie(const std::string & _title, int & _rank);
  std::string getTitle() const;
  uint getRank() const;
};

std::ostream & operator<<(std::ostream & strm, const Movie & arg);

