#ifndef INTRODUCTIONPROJECT_CLIENTREPOSITORY_H
#define INTRODUCTIONPROJECT_CLIENTREPOSITORY_H
#include "typedefs.h"
#include <vector>
#include "Repository.h"
class ClientRepository: public Repository<Client>
{
public:
    ClientRepository();
    virtual ~ClientRepository();
};
#endif //INTRODUCTIONPROJECT_CLIENTREPOSITORY_H
