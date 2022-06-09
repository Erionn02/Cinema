//
// Created by student on 06.06.2022.
//

#include "GUI/UserAddMoney.h"
#include "GUI/UserPanel.h"
#include "model/Client.h"
#include "ServerStuff/functions.h"

wxBEGIN_EVENT_TABLE(UserAddMoney,wxFrame)
                EVT_BUTTON(59, UserAddMoney::addMoney)
                EVT_BUTTON(60, UserAddMoney::goToPrevious)
wxEND_EVENT_TABLE()
UserAddMoney::UserAddMoney(wxFrame *parent) : MyFrame(parent,wxID_ANY,"Doladowywanie srodkow na konto",wxPoint(750,290),wxSize(375,250),wxMINIMIZE_BOX | wxCLOSE_BOX)
{
    info = new wxStaticText(this,wxID_ANY,"Wprowadz o ile chcesz zwiekszyc stan swojego konta: \n(<=5000)",wxPoint(10,60));
    wxBitmap bitmap(wxT("../../Images/Undo-icon1.xpm"));
    goBack = new wxBitmapButton(this, 60, bitmap, wxPoint(320,10), wxSize(40,40));
    wxTextValidator textVal2(wxFILTER_EMPTY|wxFILTER_DIGITS);
    input = new wxTextCtrl(this,wxID_ANY,"",wxPoint(10,100),wxSize(250,50),0,textVal2);
    confirm = new wxButton(this,59,"Zatwierdz",wxPoint(260,100),wxSize(95,50));
}

UserAddMoney::~UserAddMoney() {

}

void UserAddMoney::goToPrevious(wxCommandEvent &evt) {
    this->Close(true);
}

void UserAddMoney::addMoney(wxCommandEvent &evt) {
    std::string val = input->GetValue().ToStdString();
    if(val.length())
    {
        int amount = std::stoi(val);
        if(amount<=5000) {
            ClientPtr tmp = static_cast<UserPanel *>(this->GetParent())->getThisClient();
            double currentSaldo = tmp->getBalance();
            tmp->setBalance(currentSaldo + amount);
            std::string parsedClient = convertClientToStr(tmp);
            exchangeInfoWithServer("changeActiveUserState_", parsedClient);
            wxMessageBox(wxString("Konto doladowane!"), wxT("Zmiana stanu konta"), wxICON_INFORMATION);
            static_cast<UserPanel *>(this->GetParent())->updateClientInfo();
            this->Close(true);
        }
        else wxMessageBox(wxString("Wprowadzono zbyt duza kwote!"), wxT("Zmiana stanu konta"), wxICON_INFORMATION);
    } else{
        wxMessageBox( wxString("Niepoprawne dane"), wxT("Zmiana stanu konta"), wxICON_INFORMATION);
    }
}
