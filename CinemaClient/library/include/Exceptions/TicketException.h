//
// Created by student on 19.05.2022.
//

#ifndef INTRODUCTIONPROJECT_TICKETEXCEPTION_H
#define INTRODUCTIONPROJECT_TICKETEXCEPTION_H
#include "Exceptions/CinemaException.h"
class TicketException:public CinemaException {
public:
    TicketException(const std::string &arg);
};


#endif //INTRODUCTIONPROJECT_TICKETEXCEPTION_H
