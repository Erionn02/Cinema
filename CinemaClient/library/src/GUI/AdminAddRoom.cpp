//
// Created by student on 04.06.2022.
//

#include "GUI/AdminAddRoom.h"
#include "ServerStuff/functions.h"
#include "GUI/AdminRoomsFrame.h"
wxBEGIN_EVENT_TABLE(AdminAddRoom,wxFrame)
                EVT_BUTTON(1301, AdminAddRoom::add)
                EVT_BUTTON(1302,AdminAddRoom::doNothing)
wxEND_EVENT_TABLE()

AdminAddRoom::~AdminAddRoom() {

}
AdminAddRoom::AdminAddRoom(wxFrame *parent,wxWindowID id) : MyFrame(parent,id,"Dodawanie nowego filmu",wxPoint(750,290),wxSize(375,250),wxMINIMIZE_BOX | wxCLOSE_BOX)
    {
        info = new wxStaticText(this,1300,"Czy na pewno chcesz utworzyc nowa sale kinowa?",wxPoint(20,10));
        confirm = new wxButton(this,1301,"TAK",wxPoint(10,70),wxSize(170,150));
        deny = new wxButton(this,1302,"NIE",wxPoint(190,70),wxSize(170,150));
    }

void AdminAddRoom::add(wxCommandEvent &evt) {
    int id = getID();
    SRM.addScreeningRoom(id);
    exchangeInfoWithServer("registerScreeningRoom_",std::to_string(id)+"|");
    static_cast<AdminRoomsFrame*>(this->GetParent())->updateBarStatus("Ilosc sal kinowych: "+std::to_string(SRM.getSize()));
    this->Close();
    static_cast<AdminRoomsFrame*>(this->GetParent())->refresh();
}

void AdminAddRoom::doNothing(wxCommandEvent &evt) {
    this->Close();
}
