#include "model/Junior.h"
#include "model/Client.h"

std::string Junior::getTypeInfo() {
    return "Typ klienta: Junior";
}

Junior::Junior(double discount) : ClientType(discount) {}

Junior::~Junior() {}


