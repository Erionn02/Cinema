//
// Created by student on 14.05.2022.
//

#ifndef INTRODUCTIONPROJECT_SCREENINGROOM_H
#define INTRODUCTIONPROJECT_SCREENINGROOM_H
#include "typedefs.h"
#include <vector>
#include <boost/date_time.hpp>
#include <cstring>
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
struct ar{
    bool t[16][32];  //z góry ustalony rozmiar sal kinowych, 16 rzędów a w każdym 32 miejsc
};

class ScreeningRoom {
    int id;
    std::vector<arPtr> t;  // wektor odpowiadajaca indeksom, okresla zajetosc sali dla kazdego filmu
    std::vector<MoviePtr> movies;   // wektor filmow
public:
    ScreeningRoom(int id);
    int getId() const;
    const std::vector<arPtr> &getT() const;
    const std::vector<MoviePtr> &getMovies() const;
    int getMovieIndex(MoviePtr movie) const;
    int getSize()const;
    std::string getMoviesInfo()const;
    void addMovie(MoviePtr movie);
    void deleteMovie(MoviePtr movie);
    bool canAdd(pt::ptime start,pt::ptime end);
    bool isSeatValid(int row, int column,MoviePtr movie);
    void rentSeat(int row, int column, MoviePtr movie);
    int getIndexById(int id);
    int getBoughtPlaces(MoviePtr m);
    std::string getInfo()const;
    std::string getGeneralInfo()const;
    std::string nearestPlayed()const;
};


#endif //INTRODUCTIONPROJECT_SCREENINGROOM_H
