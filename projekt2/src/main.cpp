#include <iostream>
#include "../inc/FileRead.hh"

int main(){
  std::string path = "../plik.csv";
  FileInput file(path);

  if(file.open(std::ios_base::in)){
    while(!file.endOfFile()){
      std::cout << file.readLine() << std::endl;
    }
  }
  
  return 0;
}
