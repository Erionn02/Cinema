//
// Created by student on 19.05.2022.
//

#ifndef INTRODUCTIONPROJECT_SCREENINGROOMEXCEPTION_H
#define INTRODUCTIONPROJECT_SCREENINGROOMEXCEPTION_H

#include "CinemaException.h"
class ScreeningRoomException :public CinemaException{
public:
    ScreeningRoomException(const std::string &arg);
};


#endif //INTRODUCTIONPROJECT_SCREENINGROOMEXCEPTION_H
