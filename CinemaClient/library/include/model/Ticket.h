//
// Created by student on 14.05.2022.
//

#ifndef INTRODUCTIONPROJECT_TICKET_H
#define INTRODUCTIONPROJECT_TICKET_H
#include "typedefs.h"
#include <string>
class Ticket {
double price;
SegmentType row;
int column;
MoviePtr movie;
public:
    Ticket(MoviePtr movie,SegmentType row, int column);
    //celowy brak setterów, pola są niezmienne od stworzenia obiektu
    virtual ~Ticket();

    double getPrice() const;

    const MoviePtr &getMovie() const;

    SegmentType getRow() const;

    int getColumn() const;
    std::string getTicketInfo();
};


#endif //INTRODUCTIONPROJECT_TICKET_H
