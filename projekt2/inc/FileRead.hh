#pragma once

#include <fstream>
#include <istream>
#include <exception>

class FileInput{
  std::string path;
  std::fstream file;

  public:
  FileInput(const std::string & path);
  FileInput(char * path);
  bool open(std::ios_base::openmode _mode = std::ios_base::in | std::ios_base::out);
  std::string readLine();
  bool endOfFile();

  ~FileInput();
};