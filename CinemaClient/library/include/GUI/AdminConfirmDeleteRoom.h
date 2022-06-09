//
// Created by student on 05.06.2022.
//

#ifndef CINEMA_ADMINCONFIRMDELETEROOM_H
#define CINEMA_ADMINCONFIRMDELETEROOM_H

#include "MyFrame.h"
class AdminConfirmDeleteRoom :public MyFrame{
public:
    AdminConfirmDeleteRoom(wxFrame* parent, wxWindowID id);
    virtual ~AdminConfirmDeleteRoom();
    void deleteRoom(wxCommandEvent &evt);
    void doNothing(wxCommandEvent &evt);
private:
    wxButton* confirm;
    wxButton* deny;
    wxStaticText* info;
DECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINCONFIRMDELETEROOM_H
