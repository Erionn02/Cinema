#ifndef INTRODUCTIONPROJECT_MOVIEREPOSITORY_H
#define INTRODUCTIONPROJECT_MOVIEREPOSITORY_H

#include "typedefs.h"
#include <vector>
#include "Repository.h"
class MovieRepository:public Repository<Movie>
{
public:
    MovieRepository();

    virtual ~MovieRepository();
};

#endif //INTRODUCTIONPROJECT_MOVIEREPOSITORY_H
