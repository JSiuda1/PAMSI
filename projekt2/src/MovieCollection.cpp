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
}

std::vector<Movie> MovieDataBase::getMovieCollection() const{
  return collection;
}

void MovieDataBase::mergeSort(){
  sort::mergeSort(collection, 0, collection.size());
}

void MovieDataBase::quickSort(){
  sort::quickSort(collection, 0, collection.size() - 1);
}

void MovieDataBase::bucketSort(const size_t & bucketNumber){
  sort::bucketSort(collection, bucketNumber);
}

void MovieDataBase::clearImportedMovies(){
  collection.clear();
}

//PRIVATE

void MovieDataBase::getDataFromFile(std::vector<std::string> & data, unsigned int long elements){
  unsigned int i = 0;
  if(elements == 0) elements = UINT32_MAX;
  
  while(file.endOfFile() == false && i < elements){
    try{
      data.push_back(file.readLine());
    }catch(std::exception e){
      throw;
    }

    i++;
  }
}

unsigned int MovieDataBase::filtrReadedData(std::vector<std::string> & data, char delimiter, unsigned int numbersOfDelimiter){
  unsigned int erasedElements = 0;
  int delimiterFounded = 0;
  size_t position = 0;
  size_t stringLasElemPos = 0;
  
  for(int i=0; i < data.size(); i++){
    do{
      position = data[i].find(delimiter, position + 1);
      if(position != std::string::npos){
        delimiterFounded += 1;
      }
    }while(position != std::string::npos);
    //check if string contains numberOfDelimieter delimiters 
    if(delimiterFounded != numbersOfDelimiter){
      data.erase(data.begin() + i);
      i--;
      erasedElements++;
    //check if first element is a number
    }else if((data[i].front() < '0' || data[i].front() > '9')){
      data.erase(data.begin() + i);
      i--;
      erasedElements++;
    //check if last elemen is a number
    }else if(data[i].back () < '0' || data[i].back() > '9'){
      data.erase(data.begin() + i);
      i--;
      erasedElements++;
    }

    delimiterFounded = 0;
    position = 0;
  }

  return erasedElements;
}

Movie MovieDataBase::convertStringToMovie(const std::string & _str, char delimiter){
  Movie movie;
  std::string title;
  std::string str = _str;
  float rank = 0;
  //erase first element
  str.erase(0, str.find(delimiter) + 1);

  //get title
  title = str.substr(0, str.find(delimiter));

  str.erase(0, str.find(delimiter) + 1);

  rank = std::stof(str);
  
  movie.setMovie(title, rank);

  return movie;
}


std::ostream & operator<<(std::ostream & strm, const MovieDataBase & arg){
  std::vector<Movie> vec = arg.getMovieCollection();
  for(Movie var : vec){
    strm << var;
    strm << '\n';
  }

  return strm;
}