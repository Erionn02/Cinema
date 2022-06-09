//
// Created by student on 16.05.2022.
//

#ifndef INTRODUCTIONPROJECT_MOVIEMANAGER_H
#define INTRODUCTIONPROJECT_MOVIEMANAGER_H
#include "repositories/MovieRepository.h"
#include "typedefs.h"
#include <boost/date_time.hpp>
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
class MovieManager {
MovieRepository futureMovies;
MovieRepository pastMovies;
public:
    virtual ~MovieManager();
    MoviePtr addMovie(int id,const std::string &title, const pt::ptime &start, const int &time, int ageRequired,
                  const std::string &type, const ScreeningRoomPtr &screeningRoom,const double &price);
    void endMovie(MoviePtr movie);
    MoviePtr getMovie(int id, bool flag=true)const;//flagi są po to, żeby nie powielać metod. Domyślnie flaga ustawiona na true
                                                    //co oznacza że metoda realizuje dzialania dla pola futureMovies, w przeciwnym wypadku dla pastMovies
    std::vector<MoviePtr> findMovies(MoviePredicate p,bool flag=true)const;

    std::string getMovieInfo(MoviePtr movie)const;
    std::string getMoviesInfo(bool flag=true)const;

    const MovieRepository &getFutureMovies() const;

    void setFutureMovies(const MovieRepository &futureMovies);

    void setPastMovies(const MovieRepository &pastMovies);

    const MovieRepository &getPastMovies() const;
    int getSize(bool flag=true)const;

};


#endif //INTRODUCTIONPROJECT_MOVIEMANAGER_H
