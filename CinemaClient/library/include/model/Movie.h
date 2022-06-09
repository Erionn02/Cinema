#ifndef INTRODUCTIONPROJECT_MOVIE_H
#define INTRODUCTIONPROJECT_MOVIE_H
#include <string>
#include <boost/date_time.hpp>
#include "typedefs.h"

namespace pt = boost::posix_time;

class Movie{
    int id;
    std::string title;
    bool ended;
    pt::ptime start;
    int time;
    pt::ptime end;
    int ageRequired;
    std::string type;
    ScreeningRoomPtr ScreeningRoom;
    double price;
public:
    double getPrice() const;

public:
    Movie(int id,const std::string &title, const pt::ptime &start, const int &time, int ageRequired,
          const std::string &type, const ScreeningRoomPtr &screeningRoom,const double &price=0);
    //celowy brak implementacji setterów
    const std::string &getTitle() const;

    virtual ~Movie();

    int getId() const;

    bool isEnded() const;

    const pt::ptime &getStart() const;

    int getTime() const;

    const pt::ptime &getEnd() const;

    int getAgeRequired() const;

    const std::string &getType() const;

    const ScreeningRoomPtr &getScreeningRoom() const;

    std::string getMovieInfo() const;

    std::string getInfo()const;

    void setEnded(bool ended);
};


#endif //INTRODUCTIONPROJECT_MOVIE_H
