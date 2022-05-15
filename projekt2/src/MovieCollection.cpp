#include "../inc/MovieCollection.hh"

MovieDataBase::MovieDataBase(const std::string & path):
  file(File(path))
{}

MovieDataBase::MovieDataBase(char* path):
  file(File(path))
{}

bool MovieDataBase::openDataBaseFile(){
  return file.open();
}

void MovieDataBase::closeDataBaseFile(){
  file.close();
}

unsigned int MovieDataBase::getStringDataFromFile(std::string* data, unsigned int long elements){
  unsigned int i = 0;
  if(elements == 0) elements = UINT32_MAX;

  file.setOnBegin();

  while(file.endOfFile() == false && i < elements){
    try{
      data[i] = file.readLine();
    }catch(std::exception e){
      throw;
    }
    i++;
  }

  if(file.endOfFile() == true){
    //resize array;
  }

  return i;
}

unsigned int MovieDataBase::filtrStringData(std::string* data, size_t  size ,char delimiter, unsigned int numbersOfDelimiter){
  unsigned int erasedElements = 0;
  int delimiterFounded = 2;
  size_t position = 0;
  size_t stringLasElemPos = 0;
  std::string *temp = new std::string[size]; //oversized
  size_t tempIter = 0;
  
  for(int i=0; i < size; i++){
    do{
      position = data[i].find(delimiter, position + 1);
      if(position != std::string::npos){
        delimiterFounded += 1;
      }
    }while(position != std::string::npos);

    if(delimiterFounded != numbersOfDelimiter){
      erasedElements++;
    //check if first element is a number
    }else if((data[i].front() < '0' || data[i].front() > '9')){
      erasedElements++;
    //check if last elemen is a number
    }else if(data[i].back () < '0' || data[i].back() > '9'){
      erasedElements++;
    }else{
      temp[tempIter] = data[i];
      tempIter++;
    }

    delimiterFounded = 0;
    position = 0;
  }
  
  
  for(int i = 0; i < size; i++){
    if(i < size - erasedElements){
      data[i] = temp[i];
    }else{
      data[i] = "";
    }
  }
  delete[] temp;

  return erasedElements;
}

void MovieDataBase::convertStringToMovie(std::string* _vec, Movie* movies , size_t size, char delimiter){
  Movie movie;
  std::string title;
  float rank = 0;
  std::string str;

  for(int i=0; i < size; i++){
    //erase first element
    str = _vec[i];
    
    if(str.find(delimiter) == std::string::npos){
      throw std::logic_error("Delimiter not found");
    }
    str.erase(0, str.find(delimiter) + 1);

    //get title
    title = str.substr(0, str.find(delimiter));

    str.erase(0, str.find(delimiter) + 1);

    rank = std::stof(str);
    
    movie.setMovie(title, rank);

    movies[i] = movie;
  }
}

bool MovieDataBase::checkSortCorrectness(Movie* data, size_t size){
  for(size_t i=0; i<size-1; ++i){
    if(data[i] > data[i+1]){
      return false;
    }
  }

  return true;
}

double MovieDataBase::getAverageRank(Movie *data, size_t size){
  long double sum = 0;
  double rank = 0;
  for(size_t i = 0; i < size; ++i){
    rank = static_cast<double>(data[i]);
    sum += rank;
  }

  return sum/size;
}

double MovieDataBase::getMediana(Movie *data, size_t size){
  double mediana = 0;
  if(size % 2 == 0){
    mediana = static_cast<double>(data[(size/2) - 1]) + static_cast<double>(data[size/2]);
    mediana = mediana / 2;
  }else{
    mediana = static_cast<double>(data[size/2]);
  }

  return mediana;
}

