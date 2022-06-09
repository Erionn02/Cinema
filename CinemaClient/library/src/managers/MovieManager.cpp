//
// Created by student on 16.05.2022.
//

#include "managers/MovieManager.h"
#include "model/Movie.h"
#include "Exceptions/MovieException.h"
#include "model/ScreeningRoom.h"
MovieManager::~MovieManager() {

}

const MovieRepository &MovieManager::getFutureMovies() const{
    return futureMovies;
}

const MovieRepository &MovieManager::getPastMovies() const {
    return pastMovies;
}

MoviePtr MovieManager::addMovie(int id,const std::string &title, const pt::ptime &start, const int &time, int ageRequired,
                            const std::string &type, const ScreeningRoomPtr &screeningRoom,const double &price) {
    pt::ptime anEnd = start + pt::minutes(time);
    if(!screeningRoom) throw MovieException("Given screening room does not exist");
    if(!screeningRoom->canAdd(start,anEnd)) throw MovieException("There is a movie played in this time, try different start or different screening room");
    if(start>pt::second_clock::local_time())
    {   MoviePtr movie = std::make_shared<Movie>(id,title,start,time,ageRequired,type,screeningRoom,price);
        futureMovies.add(movie);
        screeningRoom->addMovie(movie);
        return movie;
    }
    else throw MovieException("Start date can not be set as past date");
}

void MovieManager::endMovie(MoviePtr movie) {
    if(movie) {
        futureMovies.remove(movie);
        movie->getScreeningRoom()->deleteMovie(movie);
        pastMovies.add(movie);
    } else throw MovieException("Given movie does not exist");
}

MoviePtr MovieManager::getMovie(int id, bool flag) const {
    if(flag)return futureMovies.getObject(id);
    return pastMovies.getObject(id);
}

std::vector<MoviePtr> MovieManager::findMovies(MoviePredicate p, bool flag) const {
    if(flag)return futureMovies.findBy(p);
    return pastMovies.findBy(p);
}

std::string MovieManager::getMovieInfo(MoviePtr movie) const {
    if (movie)return movie->getMovieInfo();
    throw MovieException("Given movie does not exist");
}
std::string MovieManager::getMoviesInfo(bool flag) const {
    if(flag)return futureMovies.getObjectsInfo();
    return pastMovies.getObjectsInfo();
}

int MovieManager::getSize(bool flag) const {
    if(flag)return futureMovies.getSize();
    return pastMovies.getSize();
}

void MovieManager::setFutureMovies(const MovieRepository &futureMovies) {
    MovieManager::futureMovies = futureMovies;
}

void MovieManager::setPastMovies(const MovieRepository &pastMovies) {
    MovieManager::pastMovies = pastMovies;
}
