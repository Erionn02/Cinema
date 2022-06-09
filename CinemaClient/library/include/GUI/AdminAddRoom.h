//
// Created by student on 04.06.2022.
//

#ifndef CINEMA_ADMINADDROOM_H
#define CINEMA_ADMINADDROOM_H
#include "MyFrame.h"

class AdminAddRoom :public MyFrame{
public:
    AdminAddRoom(wxFrame* parent, wxWindowID id);
    virtual ~AdminAddRoom();
    void add(wxCommandEvent &evt);
    void doNothing(wxCommandEvent &evt);
private:
    wxButton* confirm;
    wxButton* deny;
    wxStaticText* info;
    DECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINADDROOM_H
