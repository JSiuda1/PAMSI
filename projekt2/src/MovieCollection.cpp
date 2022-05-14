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
/*
unsigned int MovieDataBase::getMoviesFromFile(unsigned int elements, char delimiter){
  std::vector<std::string> raw_data;
  unsigned int erasedData;

  try{
    getDataFromFile(raw_data, elements);
  }catch(std::exception e){
    throw;
  }
  
  erasedData = filtrReadedData(raw_data, delimiter, 2);
  
  for(auto var : raw_data){
    collection.push_back(convertStringToMovie(var, delimiter));
  }

  return erasedData;
}*/


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

unsigned int MovieDataBase::filtrStringData(std::string* data, size_t  & size ,char delimiter, unsigned int numbersOfDelimiter){
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

/*
std::ostream & operator<<(std::ostream & strm, const MovieDataBase & arg){
  std::vector<Movie> vec = arg.getMovieCollection();
  for(Movie var : vec){
    strm << var;
    strm << '\n';
  }

  return strm;
}*/