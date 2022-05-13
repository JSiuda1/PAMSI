#include "../inc/FileRead.hh"

File::File(const std::string & _path):
  path(_path)
  {}

File::File(char * _path){
  path = std::string(_path);
}

File::File(const File & arg){
  path = arg.path;
}

void File::setPath(const std::string & _path){
  path = _path;
}

void File::setPath(char* _path){
  path = std::string(_path);
}

void File::setOnBegin(){
  file.seekg(0, std::ios::beg);
}

bool File::open(std::ios_base::openmode _mode){
  file.open(path, _mode);

  if(file.good() && file.is_open()){
    return true; //succesfull open
  }else if(file.is_open()){
    file.close(); //file is not good 
  }

  return false;
}

std::string File::readLine(){
  std::string result = {};
  
  if(file.good() == false){
    throw std::logic_error("File error");
  }else if(file.eof()){
    throw std::range_error("End of file");
  }

  getline(file, result);
  return result;
}

bool File::writeLinie(std::string _line){
  if(file.good()){
    file << _line;
    return true;
  }

  return false;
}

bool File::endOfFile(){
  return file.eof();
}

void File::close(){
  if(file.is_open()){
    file.close();
  }
}

File::~File(){
  if(file.is_open()){
    file.close();
  }
}