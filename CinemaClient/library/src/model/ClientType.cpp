#include "model/ClientType.h"

double ClientType::applyDiscount(double cena) {
    return discount * cena;
}

std::string ClientType::getTypeInfo() {
    return "";
}

ClientType::ClientType(double discount) : discount(discount) {}

ClientType::~ClientType() {

}


