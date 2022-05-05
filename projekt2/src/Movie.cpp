#include "../inc/Movie.hh"

Movie::Movie(const std::string & _title, const float & _rank):
    title(_title),
    rank(_rank)
{}

Movie::Movie(const char* _title, const float & _rank):
    title(std::string(_title)),
    rank(_rank)
{}

std::string Movie::getTitle() const{
    return title;
}

float Movie::getRank() const{
    return rank;
}

void Movie::setMovie(const std::string & _title, float & _rank){
    title = _title;
    rank = _rank;
}

bool Movie::operator< (const Movie & rhs) const{
    if(this->rank == rhs.rank){
        return this->title.compare(rhs.title) < 0 ? true : false; 
    }else{
        return this->rank < rhs.rank; 
    }
}

bool Movie::operator> (const Movie & rhs) const{
    if(this->rank == rhs.rank){
        return this->title.compare(rhs.title) < 0 ? true : false; 
    }else{
        return this->rank > rhs.rank; 
    }
}

bool Movie::operator<= (const Movie & rhs) const{
    if(this->rank == rhs.rank){
        return this->title.compare(rhs.title) < 0 ? true : false; 
    }else{
        return this->rank <= rhs.rank; 
    }
}

bool Movie::operator>= (const Movie & rhs) const{
    if(this->rank == rhs.rank){
        return this->title.compare(rhs.title) < 0 ? true : false; 
    }else{
        return this->rank >= rhs.rank; 
    }
}

Movie::operator int(){
  return static_cast<int>(this->rank);
}


std::ostream & operator<<(std::ostream & strm, const Movie & arg){
    strm << "Title: ";
    strm << arg.getTitle();
    strm << "\t Rank: ";
    strm << arg.getRank();

    return strm;
}

