//
// Created by student on 05.06.2022.
//

#include "GUI/AdminConfirmUnregisterUser.h"
#include "ServerStuff/functions.h"
#include "GUI/AdminUsersFrame.h"
wxBEGIN_EVENT_TABLE(AdminConfirmUnregisterUser,wxFrame)
                EVT_BUTTON(1301, AdminConfirmUnregisterUser::deleteUser)
                EVT_BUTTON(1302,AdminConfirmUnregisterUser::doNothing)
wxEND_EVENT_TABLE()

AdminConfirmUnregisterUser::AdminConfirmUnregisterUser(wxFrame *parent,wxWindowID id) : MyFrame(parent,id,"Dodawanie nowego filmu",wxPoint(750,290),wxSize(375,250),wxMINIMIZE_BOX | wxCLOSE_BOX)
{
    info = new wxStaticText(this,1300,"Czy na pewno chcesz wyrejestrowac uzytkownika?",wxPoint(20,10));
    confirm = new wxButton(this,1301,"TAK",wxPoint(10,70),wxSize(170,150));
    deny = new wxButton(this,1302,"NIE",wxPoint(190,70),wxSize(170,150));
}
AdminConfirmUnregisterUser::~AdminConfirmUnregisterUser() {

}

void AdminConfirmUnregisterUser::deleteUser(wxCommandEvent &evt) {
    int id = static_cast<AdminUsersFrame*>(this->GetParent())->getCurrentUserId();
    ClientPtr tmp = CM.getClient(id);
    CM.unRegisterClient(tmp);
    std::string parsed_client = convertClientToStr(tmp);
    exchangeInfoWithServer("unregisterClient_",parsed_client);
    static_cast<AdminUsersFrame*>(this->GetParent())->refresh();
    static_cast<AdminUsersFrame*>(this->GetParent())->updateBarStatus("Ilosc uzytkownikow: "+std::to_string(CM.getSize()));
    this->Close();
}

void AdminConfirmUnregisterUser::doNothing(wxCommandEvent &evt) {
    this->Close();
}
