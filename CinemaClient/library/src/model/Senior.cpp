#include "model/Senior.h"

std::string Senior::getTypeInfo() {
    return "Typ klienta: Senior";
}

Senior::Senior(double discount) : ClientType(discount) {}

Senior::~Senior() {

}
