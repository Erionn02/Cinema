//
// Created by student on 05.06.2022.
//

#include "GUI/AdminConfirmDeleteRoom.h"
#include "ServerStuff/functions.h"
#include "GUI/AdminRoomsFrame.h"

wxBEGIN_EVENT_TABLE(AdminConfirmDeleteRoom,wxFrame)
                EVT_BUTTON(1301, AdminConfirmDeleteRoom::deleteRoom)
                EVT_BUTTON(1302,AdminConfirmDeleteRoom::doNothing)
wxEND_EVENT_TABLE()

AdminConfirmDeleteRoom::~AdminConfirmDeleteRoom() {

}
AdminConfirmDeleteRoom::AdminConfirmDeleteRoom(wxFrame *parent,wxWindowID id) : MyFrame(parent,id,"Dodawanie nowego filmu",wxPoint(750,290),wxSize(375,250),wxMINIMIZE_BOX | wxCLOSE_BOX)
{
    info = new wxStaticText(this,1300,"Czy na pewno chcesz usunac sale kinowa?",wxPoint(20,10));
    confirm = new wxButton(this,1301,"TAK",wxPoint(10,70),wxSize(170,150));
    deny = new wxButton(this,1302,"NIE",wxPoint(190,70),wxSize(170,150));
}

void AdminConfirmDeleteRoom::deleteRoom(wxCommandEvent &evt) {
    int id = static_cast<AdminRoomsFrame*>(this->GetParent())->getCurrentRoomId();
    SRM.deleteScreeningRoom(SRM.findById(id));
    exchangeInfoWithServer("deleteRoom_",std::to_string(id)+"|");
    static_cast<AdminRoomsFrame*>(this->GetParent())->refresh();
    static_cast<AdminRoomsFrame*>(this->GetParent())->updateBarStatus("Ilosc sal kinowych: "+std::to_string(SRM.getSize()));
    this->Close();
}

void AdminConfirmDeleteRoom::doNothing(wxCommandEvent &evt) {
    this->Close();
}
