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


unsigned int MovieDataBase::getStringDataFromFile(std::vector<std::string> & data, unsigned int long elements){
  unsigned int i = 0;
  if(elements == 0) elements = UINT32_MAX;
  
  file.setOnBegin();

  while(file.endOfFile() == false && i < elements){
    try{
      data.push_back(file.readLine());
    }catch(std::exception e){
      throw;
    }
    i++;
  }

  return i;
}

unsigned int MovieDataBase::filtrStringData(std::vector<std::string> & data, char delimiter, unsigned int numbersOfDelimiter){
  unsigned int erasedElements = 0;
  int delimiterFounded = 2;
  size_t position = 0;
  size_t stringLasElemPos = 0;
  std::vector<std::string> temp = data;
  data.clear();

  for(int i=0; i < temp.size(); i++){
    do{
      position = temp[i].find(delimiter, position + 1);
      if(position != std::string::npos){
        delimiterFounded += 1;
      }
    }while(position != std::string::npos);

    if(delimiterFounded != numbersOfDelimiter){

      erasedElements++;
    //check if first element is a number
    }else if((temp[i].front() < '0' || temp[i].front() > '9')){
      erasedElements++;
    //check if last elemen is a number
    }else if(temp[i].back () < '0' || temp[i].back() > '9'){
      erasedElements++;
    }else{
      data.push_back(temp[i]);
    }

    delimiterFounded = 0;
    position = 0;
  }

  return erasedElements;
}

void MovieDataBase::convertStringToMovie(const std::vector<std::string> & _vec, std::vector<Movie> & movies ,char delimiter){
  Movie movie;
  std::string title;
  float rank = 0;
  
  for(std::string str: _vec){
    //erase first element
    if(str.find(delimiter) == std::string::npos){
      throw std::logic_error("Delimiter not found");
    }
    str.erase(0, str.find(delimiter) + 1);

    //get title
    title = str.substr(0, str.find(delimiter));

    str.erase(0, str.find(delimiter) + 1);

    rank = std::stof(str);
    
    movie.setMovie(title, rank);

    movies.push_back(movie);
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