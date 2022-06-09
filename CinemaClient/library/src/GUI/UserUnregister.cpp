//
// Created by student on 06.06.2022.
//

#include "GUI/UserUnregister.h"
#include "GUI/UserPanel.h"
#include "ServerStuff/functions.h"

wxBEGIN_EVENT_TABLE(UserUnregister,wxFrame)
                EVT_BUTTON(1301, UserUnregister::unregister)
                EVT_BUTTON(1302,UserUnregister::doNothing)
wxEND_EVENT_TABLE()

UserUnregister::UserUnregister(wxFrame *parent) : MyFrame(parent,wxID_ANY,"Usuwanie konta",wxPoint(750,290),wxSize(375,250),wxMINIMIZE_BOX | wxCLOSE_BOX)
{
    info = new wxStaticText(this,1300,"Czy na pewno chcesz wyrejestrowac swoje konto?",wxPoint(20,10));
    confirm = new wxButton(this,1301,"TAK",wxPoint(10,70),wxSize(170,150));
    deny = new wxButton(this,1302,"NIE",wxPoint(190,70),wxSize(170,150));
}

UserUnregister::~UserUnregister() {

}

void UserUnregister::unregister(wxCommandEvent &evt) {
    ClientPtr tmp = static_cast<UserPanel*>(this->GetParent())->getThisClient();
    CM.unRegisterClient(tmp);
    std::string parsedClient = convertClientToStr(tmp);
    exchangeInfoWithServer("unregisterClient_",parsedClient);
    wxMessageBox( wxString("Twoje konto zostalo wyrejestrowane!"), wxT("Usuwanie konta"), wxICON_INFORMATION);
    this->Close(true);
    this->GetParent()->Close(true);
    this->GetParent()->GetParent()->Show(true);
}

void UserUnregister::doNothing(wxCommandEvent &evt) {
    this->Close(true);
}
