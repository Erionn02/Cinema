//
// Created by student on 14.05.2022.
//

#include "model/Ticket.h"
#include "model/Movie.h"
#include "model/ScreeningRoom.h"
#include "Exceptions/TicketException.h"
Ticket::Ticket(MoviePtr movie, SegmentType row, int column): row(row), column(column),movie(movie)
{
    if(!movie) throw TicketException("Given movie does not exist!");
    if(!movie->getScreeningRoom()->isSeatValid(row,column,movie)) throw TicketException("Given seat is already occupied");
    if(row>15 || row<0 || column >32 || column <0)throw TicketException("Given seat does not exist");
    price=movie->getPrice();
    movie->getScreeningRoom()->rentSeat(row,column,movie);
}

double Ticket::getPrice() const {
    return price;
}

SegmentType Ticket::getRow() const {
    return row;
}

int Ticket::getColumn() const {
    return column;
}

std::string Ticket::getTicketInfo() {
    std::string letter="";
    switch(row)
    {
        case A:{
            letter="A";
            break;}
        case B:{
            letter="B";
            break;}
        case C:{
            letter="C";
            break;}
        case D:{
            letter="D";
            break;}
        case E:{
            letter="E";
            break;}
        case F:{
            letter="F";
            break;}
        case G:{
            letter="G";
            break;}
        case H:{
            letter="H";
            break;}
        case I:{
            letter="I";
            break;}
        case J:{
            letter="J";
            break;}
        case K:{
            letter="K";
            break;}
        case L:{
            letter="L";
            break;}
        case M:{
            letter="M";
            break;}
        case N:{
            letter="N";
            break;}
        case O:{
            letter="O";
            break;}
        case P:{
            letter="P";
            break;}
        case Q:{
            letter="Q";
            break;}
        case R:{
            letter="R";
            break;}
        case S:{
            letter="S";
            break;}
        case T:{
            letter="T";
            break;}
        case U:{
            letter="U";
            break;}
        case V:{
            letter="V";
            break;}
        case W:{
            letter="W";
            break;}
        case X:{
            letter="X";
            break;}
        case Y:{
            letter="Y";
            break;}
        case Z:{
            letter="Z";
            break;}
    }
    std::stringstream ss;
    ss<<movie->getStart();
    return movie->getTitle()+" "+"Cena biletu: "+ std::to_string(price)+" Rzad: "+letter+" Kolumna: "+ std::to_string(column)+" Data startu: "+ss.str()+" sala: "+std::to_string(movie->getScreeningRoom()->getId());
}

Ticket::~Ticket() {

}

const MoviePtr &Ticket::getMovie() const {
    return movie;
}

