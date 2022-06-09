//
// Created by student on 19.05.2022.
//

#ifndef INTRODUCTIONPROJECT_CINEMAEXCEPTION_H
#define INTRODUCTIONPROJECT_CINEMAEXCEPTION_H
#include <stdexcept>

class CinemaException :public std::logic_error{
public:
    CinemaException(const std::string &arg);
};


#endif //INTRODUCTIONPROJECT_CINEMAEXCEPTION_H
