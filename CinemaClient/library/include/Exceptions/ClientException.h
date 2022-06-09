//
// Created by student on 19.05.2022.
//

#ifndef INTRODUCTIONPROJECT_CLIENTEXCEPTION_H
#define INTRODUCTIONPROJECT_CLIENTEXCEPTION_H
#include "Exceptions/CinemaException.h"
class ClientException:public CinemaException {
public:
    ClientException(const std::string &arg);
};


#endif //INTRODUCTIONPROJECT_CLIENTEXCEPTION_H
