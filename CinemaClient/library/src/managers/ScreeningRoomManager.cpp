//
// Created by student on 16.05.2022.
//

#include "managers/ScreeningRoomManager.h"
#include "Exceptions/ScreeningRoomException.h"
#include "model/ScreeningRoom.h"
ScreeningRoomManager::~ScreeningRoomManager() {

}

const ScreeningRoomRepository &ScreeningRoomManager::getScreeningRooms() const {
    return screeningRooms;
}

ScreeningRoomPtr ScreeningRoomManager::addScreeningRoom(int id) {
    ScreeningRoomPtr SR = std::make_shared<ScreeningRoom>(id);
    screeningRooms.add(SR);
    return SR;
}

void ScreeningRoomManager::deleteScreeningRoom(ScreeningRoomPtr screeningRoom) {
    if(screeningRoom)
        screeningRooms.remove(screeningRoom);
    else throw ScreeningRoomException("Given screening room does not exist");
}

std::string ScreeningRoomManager::getScreeningRoomsInfo() const {
    return screeningRooms.getObjectsInfo();
}

std::string ScreeningRoomManager::getScreeningRoomInfo(ScreeningRoomPtr room) const {
    if(room)return screeningRooms.getObjectInfo(room);
    else throw ScreeningRoomException("Given screening room does not exist");
}

ScreeningRoomPtr ScreeningRoomManager::findById(int id) {
    return screeningRooms.getObject(id);
}

std::vector<MoviePtr> ScreeningRoomManager::getScreeningRoomMovies(ScreeningRoomPtr room) {
    if(room)return room->getMovies();
    throw ScreeningRoomException("Invalid screening room");
}

int ScreeningRoomManager::getSize() const {
    return screeningRooms.getSize();
}

void ScreeningRoomManager::setScreeningRooms(const ScreeningRoomRepository &screeningRooms) {
    ScreeningRoomManager::screeningRooms = screeningRooms;
}

std::vector<ScreeningRoomPtr> ScreeningRoomManager::findRooms(ScreeningRoomPredicate p) {
    return screeningRooms.findBy(p);
}
