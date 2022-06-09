#include "model/Concessionary.h"

std::string Concessionary::getTypeInfo() {
    return "Typ klienta: Ulgowy";
}

Concessionary::Concessionary(double discount) : ClientType(discount) {}

Concessionary::~Concessionary() {

}
