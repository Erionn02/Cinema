//
// Created by student on 14.05.2022.
//

#include "model/ScreeningRoom.h"
#include <algorithm>
#include <vector>
#include "model/Movie.h"
#include <cstring>
#include "Exceptions/ScreeningRoomException.h"
int ScreeningRoom::getId() const {
    return id;
}

const std::vector<arPtr> &ScreeningRoom::getT() const {
    return t;
}

const std::vector<MoviePtr> &ScreeningRoom::getMovies() const {
    return movies;
}

int ScreeningRoom::getMovieIndex(MoviePtr movie) const {
    if(!movie) throw ScreeningRoomException("Given movie is nullptr");
    for(int i=0;i<movies.size();i++)
    {
        if(movies[i]->getId()==movie->getId()) return i;
    }
    throw ScreeningRoomException("Given movie does not belong to this screeningRoom!");
}

int ScreeningRoom::getSize() const {
    return movies.size();
}

void ScreeningRoom::addMovie(MoviePtr movie) {
    if(movie)
    {
     arPtr tmp = std::make_shared<ar>();
     std::memset(tmp->t,true,16*32);
     movies.push_back(movie);
     t.push_back(tmp);
    }
    else throw ScreeningRoomException("Given movie does not exist!");
}

void ScreeningRoom::deleteMovie(MoviePtr movie) {
    if(movie){
        int ind = getMovieIndex(movie);
        movies.erase(std::remove(movies.begin(), movies.end(), movie), movies.end());
        t.erase(std::remove(t.begin(), t.end(), t[ind]), t.end());
    }else throw ScreeningRoomException("Given movie does not exist!");
}

ScreeningRoom::ScreeningRoom(int id) : id(id) {}

std::string ScreeningRoom::getMoviesInfo() const{
    std::string s="";
    for(int i=0;i<movies.size();i++)
    s+=movies[i]->getMovieInfo()+"\n";
    return s;
}

bool ScreeningRoom::canAdd(pt::ptime start, pt::ptime end) {
    bool flag=true;
    for(int i=0;i<movies.size();i++)
    {
        if(start>=movies[i]->getStart() && movies[i]->getEnd()>=start)
        {
            flag=false;
            break;
        }
        if(end>=movies[i]->getStart() && movies[i]->getEnd()>=end)
        {
            flag=false;
            break;
        }
    }
    return flag;
}

bool ScreeningRoom::isSeatValid(int row, int column, MoviePtr movie) {
    int index= getMovieIndex(movie);
    return t[index]->t[row][column];
}

void ScreeningRoom::rentSeat(int row, int column, MoviePtr movie) {
    int index= getMovieIndex(movie);
    t[index]->t[row][column]=false;
}

std::string ScreeningRoom::getInfo() const {
    return "Sala kinowa o ID:"+std::to_string(id)+"\n\n"+getMoviesInfo();
}

int ScreeningRoom::getIndexById(int id) {
    for(int i=0;i<movies.size();i++)
    {
        if(movies[i]->getId()==id) return i;
    }
    return 0;
}

std::string ScreeningRoom::getGeneralInfo() const {
    return "ID sali kinowej: "+std::to_string(id)+"   Ilosc zaplanowanych filmow na sali: "+std::to_string(movies.size());
}

std::string ScreeningRoom::nearestPlayed() const {
    pt::ptime now = pt::second_clock::local_time();
    pt::ptime min_date= pt::ptime (gr::date(2222,05,14));
    MoviePtr tmp_min;
    for(auto &movie:movies)
    {
        if(movie->getStart()<min_date && movie->getStart()>now)
        {
            tmp_min = movie;
            min_date = movie->getStart();
        }
    }
    std::string s="";
    if(tmp_min) return tmp_min->getMovieInfo();
    return s;
}

int ScreeningRoom::getBoughtPlaces(MoviePtr m) {
    int ind = getMovieIndex(m);
    arPtr p = t[ind];
    int counter = 0;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<32;j++)
        {
            if(!p->t[i][j])counter+=1;
        }
    }
    return counter;
}
