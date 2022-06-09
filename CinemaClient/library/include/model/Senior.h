#ifndef INTRODUCTIONPROJECT_SENIOR_H
#define INTRODUCTIONPROJECT_SENIOR_H
#include <iostream>
#include "typedefs.h"
#include "model/ClientType.h"
class Senior : public ClientType{
public:
    Senior(double discount = 0.2);

    virtual ~Senior();

    virtual std::string getTypeInfo ();
};


#endif //INTRODUCTIONPROJECT_SENIOR_H
