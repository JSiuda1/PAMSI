#pragma once

#include <fstream>
#include <istream>
#include <exception>

class File{
  std::string path;
  std::fstream file;

  public:
  File() = default;
  File(const std::string & path);
  File(char * path);
  File(const File & arg);
  void setPath(const std::string & _path);
  void setPath(char* _path);
  bool open(std::ios_base::openmode _mode = std::ios_base::in | std::ios_base::out);
  std::string readLine();
  bool endOfFile();
  void close();

  ~File();
};