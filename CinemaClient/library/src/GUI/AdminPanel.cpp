
#include "GUI/AdminPanel.h"
#include "GUI/AdminMoviesFrame.h"
#include "GUI/AdminRoomsFrame.h"
#include "GUI/AdminUsersFrame.h"
wxBEGIN_EVENT_TABLE(AdminPanel,wxFrame)
                EVT_BUTTON(3001, AdminPanel::onButtonClickedUsers)
                EVT_BUTTON(3002, AdminPanel::onButtonClickedMovies)
                EVT_BUTTON(3003, AdminPanel::onButtonClickedRooms)
wxEND_EVENT_TABLE()

AdminPanel::~AdminPanel() {

}

AdminPanel::AdminPanel(wxFrame *parent, wxPoint location):MyFrame(parent,3000,"Panel wyboru",location,wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX){
    usersButton = new wxButton(this,3001,"Zarzadzaj uzytkownikami",wxPoint(100,270),wxSize(266,200));
    moviesButton = new wxButton(this,3002,"Zarzadzaj filmami",wxPoint(466,270),wxSize(266,200));
    roomsButton = new wxButton(this,3003,"Zarzadzaj salami kinowymi",wxPoint(832,270),wxSize(266,200));
    wxBitmap bitmap(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *button = new wxBitmapButton(this, 80, bitmap, wxPoint(10,10), wxSize(40,40));
}

void AdminPanel::onButtonClickedUsers(wxCommandEvent &evt) {
    AdminUsersFrame* frame = new AdminUsersFrame(this,GetPosition());
    this->Show(false);
    frame->Show(true);
}

void AdminPanel::onButtonClickedMovies(wxCommandEvent &evt) {
    AdminMoviesFrame* frame = new AdminMoviesFrame(this,GetPosition());
    this->Show(false);
    frame->Show(true);
}

void AdminPanel::onButtonClickedRooms(wxCommandEvent &evt) {
    AdminRoomsFrame* frame = new AdminRoomsFrame(this,GetPosition());
    this->Show(false);
    frame->Show(true);
}
void AdminPanel::goBack(wxCommandEvent &evt){
    this->GetParent()->Show(true);
    this->GetParent()->SetPosition(this->GetPosition());
    this->Close(true);
}