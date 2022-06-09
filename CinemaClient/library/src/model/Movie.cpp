#include "model/Movie.h"
#include "model/ScreeningRoom.h"
#include "Exceptions/MovieException.h"
Movie::Movie(int id,const std::string &title, const pt::ptime &start,const int &time, int ageRequired,
             const std::string &type, const ScreeningRoomPtr &screeningRoom,const double &price) : title(title), ended(false), start(start),
                                                                                ageRequired(ageRequired),
                                                                               type(type),
                                                                               ScreeningRoom(screeningRoom),time(time),id(id),price(price)
 {
    if(ageRequired<0||ageRequired>18) throw MovieException("Niepoprawny wymagany wiek (0<=ageRequired<=18)");
    //if(start<=pt::second_clock::local_time())throw MovieException("Invalid start date");
    if(time<=0)throw MovieException("Invalid movie duration time");
    if(price<0)throw MovieException("Movie's price can not be set as negative");
    end=start+pt::minutes(time);
 }
const std::string &Movie::getTitle() const {
    return title;
}

bool Movie::isEnded() const {
    return ended;
}

const pt::ptime &Movie::getStart() const {
    return start;
}

int Movie::getTime() const {
    return time;
    //metoda zwraca czas trwania filmu w minutach
}

const pt::ptime &Movie::getEnd() const {
    return end;
}

int Movie::getAgeRequired() const {
    return ageRequired;
}

const std::string &Movie::getType() const {
    return type;
}
const ScreeningRoomPtr &Movie::getScreeningRoom() const {
    return ScreeningRoom;
}
std::string Movie::getMovieInfo() const {
    std::stringstream ss;
    ss << start;
    std::string s = ss.str();
    std::stringstream ss2;
    ss2 << end;
    std::string sg = ss2.str();
    return "ID filmu: "+std::to_string(id)+"   Tytul filmu: "+title+"   Typ filmu: "+type+"   Data poczatku filmu: "+s+"   Data konca filmu "+sg+"   Czas trwania filmu: "+
                                                                                   std::to_string(time)+" minut   Minimalny wiek wymagany "+std::to_string(ageRequired)+"   Cena biletu "+std::to_string(price)+" PLN";
}
void Movie::setEnded(bool end) {
    if(end) ended = end;
}

int Movie::getId() const {
    return id;
}

Movie::~Movie() {

}

std::string Movie::getInfo() const {
    return getMovieInfo();
}

double Movie::getPrice() const {
    return price;
}



