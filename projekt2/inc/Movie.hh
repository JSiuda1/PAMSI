#pragma once

#include <iostream>

class Movie{
  std::string title;
  float rank;

  public:
  Movie() = default;
  Movie(const char * _title, const float & _rank);
  Movie(const std::string & _title, const float & _rank);
  std::string getTitle() const;
  float getRank() const;
  void setMovie(const std::string & _title, float & _rank);
  bool operator< (const Movie & rhs) const;
  bool operator>(const Movie & rhs) const;
  bool operator<=(const Movie & rhs) const;
  bool operator>=(const Movie & rhs) const;
  explicit operator int(); //overload int cast
};

std::ostream & operator<<(std::ostream & strm, const Movie & arg);
