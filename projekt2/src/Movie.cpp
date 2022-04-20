#include "../inc/Movie.hh"

std::ostream & operator<<(std::ostream & strm, const Movie & arg){
    strm << "Title: ";
    strm << arg.getTitle();
    strm << "\t Rank: ";
    strm << arg.getRank();

    return strm;
}