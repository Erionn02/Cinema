//
// Created by student on 27.05.2022.
//

#include "GUI/MainFrame.h"
#include "ServerStuff/functions.h"
#include "GUI/RegisterFrame.h"
#include "repositories/ScreeningRoomRepository.h"
#include "repositories/MovieRepository.h"
#include "GUI/AdminLogin.h"
#include "GUI/UserLoginFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_BUTTON(1000, MainFrame::onButtonClickedRegister)
    EVT_BUTTON(1002, MainFrame::onButtonClickedAdmin)
    EVT_BUTTON(1003, MainFrame::onButtonClickedLogin)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(): MyFrame(nullptr,1,"Cinema Application",wxPoint(360,220),wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX) {
    wxStaticText* info = new wxStaticText(this,59, "WITAMY W KINIE SILVER SCREEN!!!", wxPoint(440, 70), wxSize(500,200));
    info->SetFont(info->GetFont().Scale(3.0));
    registerButton = new wxButton(this,1000,"Zarejestruj sie",wxPoint(32,300),wxSize(350,300));
    adminButton = new wxButton(this,1002,"Zaloguj sie jako administrator",wxPoint(811,300),wxSize(350,300));
    loginButton = new wxButton(this,1003,"Zaloguj sie jako uzytkownik",wxPoint(419,300),wxSize(350,300));

    retrieveDataBases(CM, MM, SRM);
}

MainFrame::~MainFrame() {

}

void MainFrame::onButtonClickedRegister(wxCommandEvent &evt) {
    RegisterFrame *frame = new RegisterFrame(this,GetPosition());
    frame->Show(true);
    this->Show(false);
}

void MainFrame::onButtonClickedAdmin(wxCommandEvent &evt) {
    AdminLogin *frame = new AdminLogin(this,GetPosition());
    frame->Show(true);
    this->Show(false);
}

void MainFrame::onButtonClickedLogin(wxCommandEvent &evt) {
    UserLoginFrame *frame = new UserLoginFrame(this,GetPosition());
    frame->Show(true);
    this->Show(false);
}