//
// Created by student on 06.06.2022.
//

#ifndef CINEMA_USERUNREGISTER_H
#define CINEMA_USERUNREGISTER_H
#include "MyFrame.h"

class UserUnregister :public MyFrame{
private:
    wxButton* confirm;
    wxButton* deny;
    wxStaticText* info;
public:
    UserUnregister(wxFrame* parent);
    void unregister(wxCommandEvent &evt);
    void doNothing(wxCommandEvent &evt);
    virtual ~UserUnregister();


DECLARE_EVENT_TABLE();
};


#endif //CINEMA_USERUNREGISTER_H
