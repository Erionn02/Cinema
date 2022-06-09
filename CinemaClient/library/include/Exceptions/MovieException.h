//
// Created by student on 19.05.2022.
//

#ifndef INTRODUCTIONPROJECT_MOVIEEXCEPTION_H
#define INTRODUCTIONPROJECT_MOVIEEXCEPTION_H

#include "Exceptions/CinemaException.h"
class MovieException:public CinemaException {
public:
    MovieException(const std::string &arg);
};


#endif //INTRODUCTIONPROJECT_MOVIEEXCEPTION_H
