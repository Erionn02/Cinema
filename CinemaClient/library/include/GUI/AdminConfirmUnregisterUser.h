//
// Created by student on 05.06.2022.
//

#ifndef CINEMA_ADMINCONFIRMUNREGISTERUSER_H
#define CINEMA_ADMINCONFIRMUNREGISTERUSER_H
#include "MyFrame.h"

class AdminConfirmUnregisterUser :public MyFrame{
public:
    AdminConfirmUnregisterUser(wxFrame* parent, wxWindowID id);
    virtual ~AdminConfirmUnregisterUser();
    void deleteUser(wxCommandEvent &evt);
    void doNothing(wxCommandEvent &evt);
private:
    wxButton* confirm;
    wxButton* deny;
    wxStaticText* info;
DECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINCONFIRMUNREGISTERUSER_H
