#include "../inc/FileRead.hh"

FileInput::FileInput(const std::string & _path):
  path(_path)
  {}

FileInput::FileInput(char * _path){
  path = std::string(_path);
}

bool FileInput::open(std::ios_base::openmode _mode){
  file.open(path, _mode);

  if(file.good() && file.is_open()){
    return true; //succesfull open
  }else if(file.is_open()){
    file.close(); //file is not good 
  }

  return false;
}

std::string FileInput::readLine(){
  std::string result = {};
  
  if(file.good() == false){
    throw std::logic_error("File error");
  }else if(file.eof()){
    throw std::range_error("End of file");
  }

  getline(file, result);

  return result;
}

bool FileInput::endOfFile(){
  return file.eof();
}

FileInput::~FileInput(){
  if(file.is_open()){
    file.close();
  }
}