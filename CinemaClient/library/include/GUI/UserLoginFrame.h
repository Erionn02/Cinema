//
// Created by student on 29.05.2022.
//

#ifndef CINEMA_USERLOGINFRAME_H
#define CINEMA_USERLOGINFRAME_H
#include "MyFrame.h"

class UserLoginFrame:public MyFrame {
private:
    wxTextCtrl* login;
    wxTextCtrl* password;
    wxButton* confirm;

    wxStaticText* description_1;
    wxStaticText* description_2;
public:
    UserLoginFrame(wxFrame* parent, wxPoint point);
    void goBack(wxCommandEvent &evt);
    void onButtonClicked(wxCommandEvent &evt);
wxDECLARE_EVENT_TABLE();
};


#endif //CINEMA_USERLOGINFRAME_H