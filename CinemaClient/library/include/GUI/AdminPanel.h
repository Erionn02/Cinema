//
// Created by student on 28.05.2022.
//

#ifndef CINEMA_ADMINPANEL_H
#define CINEMA_ADMINPANEL_H
#include "MyFrame.h"

class AdminPanel :public MyFrame{
private:
    wxButton *usersButton=nullptr;
    wxButton *moviesButton=nullptr;
    wxButton *roomsButton=nullptr;
public:
    AdminPanel(wxFrame* parent, wxPoint location);
    void onButtonClickedUsers(wxCommandEvent &evt);
    void onButtonClickedMovies(wxCommandEvent &evt);
    void onButtonClickedRooms(wxCommandEvent &evt);
    void goBack(wxCommandEvent &evt);
    virtual ~AdminPanel();
wxDECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINPANEL_H
