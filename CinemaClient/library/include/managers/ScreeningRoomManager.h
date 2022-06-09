//
// Created by student on 16.05.2022.
//

#ifndef INTRODUCTIONPROJECT_SCREENINGROOMMANAGER_H
#define INTRODUCTIONPROJECT_SCREENINGROOMMANAGER_H
#include <vector>
#include "typedefs.h"
#include "repositories/ScreeningRoomRepository.h"

class ScreeningRoomManager {
ScreeningRoomRepository screeningRooms;
public:
    virtual ~ScreeningRoomManager();
    const ScreeningRoomRepository &getScreeningRooms() const;
    ScreeningRoomPtr addScreeningRoom(int id);

    void setScreeningRooms(const ScreeningRoomRepository &screeningRooms);

    void deleteScreeningRoom(ScreeningRoomPtr screeningRoom);
    std::string getScreeningRoomsInfo()const;
    std::string getScreeningRoomInfo(ScreeningRoomPtr room)const;
    ScreeningRoomPtr findById(int id);

    std::vector<ScreeningRoomPtr> findRooms(ScreeningRoomPredicate p);
    std::vector<MoviePtr> getScreeningRoomMovies(ScreeningRoomPtr room);
    int getSize()const;
};


#endif //INTRODUCTIONPROJECT_SCREENINGROOMMANAGER_H
