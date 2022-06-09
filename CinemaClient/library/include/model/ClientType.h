#ifndef INTRODUCTIONPROJECT_CLIENTTYPE_H
#define INTRODUCTIONPROJECT_CLIENTTYPE_H
#include <iostream>
#include "typedefs.h"

class ClientType {
double discount;
public:
    ClientType(double discount);

public:
    virtual ~ClientType();
    double applyDiscount(double);
    virtual std::string getTypeInfo ()=0;
};


#endif //INTRODUCTIONPROJECT_CLIENTTYPE_H
