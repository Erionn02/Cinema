#ifndef INTRODUCTIONPROJECT_JUNIOR_H
#define INTRODUCTIONPROJECT_JUNIOR_H
#include <iostream>
#include "typedefs.h"
#include "model/ClientType.h"

class Junior : public ClientType {
public:
    Junior(double discount = 1);

    virtual ~Junior();

    virtual std::string getTypeInfo ();
};


#endif //INTRODUCTIONPROJECT_JUNIOR_H
