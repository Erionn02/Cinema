//
// Created by student on 28.05.2022.
//

#ifndef CINEMA_ADMINLOGIN_H
#define CINEMA_ADMINLOGIN_H
#include "MyFrame.h"

class AdminLogin:public MyFrame {
private:
    wxTextCtrl* login;
    wxTextCtrl* password;
    wxButton* confirm;

    wxStaticText* description_1;
    wxStaticText* description_2;
wxDECLARE_EVENT_TABLE();
public:
    AdminLogin(wxFrame* parent, wxPoint point);

    virtual ~AdminLogin();
    void goBack(wxCommandEvent &evt);
    void onButtonClicked(wxCommandEvent &evt);
};


#endif //CINEMA_ADMINLOGIN_H
