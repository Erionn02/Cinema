#ifndef INTRODUCTIONPROJECT_SCREENINGROOMREPOSITORY_H
#define INTRODUCTIONPROJECT_SCREENINGROOMREPOSITORY_H

#include "typedefs.h"
#include <vector>
#include "Repository.h"
class ScreeningRoomRepository:public Repository<ScreeningRoom>
{
public:
    ScreeningRoomRepository();

    virtual ~ScreeningRoomRepository();

};
#endif //INTRODUCTIONPROJECT_SCREENINGROOMREPOSITORY_H
