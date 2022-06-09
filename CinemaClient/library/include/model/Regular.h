#ifndef INTRODUCTIONPROJECT_REGULAR_H
#define INTRODUCTIONPROJECT_REGULAR_H
#include <iostream>
#include "typedefs.h"
#include "model/ClientType.h"
class Regular : public ClientType{
public:
    Regular(double discount = 0);

    virtual ~Regular();

    virtual std::string getTypeInfo ();
};


#endif //INTRODUCTIONPROJECT_REGULAR_H
