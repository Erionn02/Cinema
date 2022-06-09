#include "model/Regular.h"

std::string Regular::getTypeInfo() {
    return "Typ klienta: Normalny";
}

Regular::Regular(double discount) : ClientType(discount) {}

Regular::~Regular() {

}
