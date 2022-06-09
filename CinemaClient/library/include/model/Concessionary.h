#ifndef INTRODUCTIONPROJECT_CONCESSIONARY_H
#define INTRODUCTIONPROJECT_CONCESSIONARY_H
#include <iostream>
#include "typedefs.h"
#include "model/ClientType.h"
class Concessionary : public ClientType{
public:

    Concessionary(double discount = 0.3);

    virtual ~Concessionary();

    virtual std::string getTypeInfo ();
};


#endif //INTRODUCTIONPROJECT_CONCESSIONARY_H
