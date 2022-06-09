//
// Created by student on 06.06.2022.
//

#ifndef CINEMA_USERADDMONEY_H
#define CINEMA_USERADDMONEY_H
#include "MyFrame.h"
class UserAddMoney :public MyFrame{
private:
    wxTextCtrl* input;
    wxButton* confirm;
    wxStaticText* info;
    wxBitmapButton* goBack;
public:
    UserAddMoney(wxFrame* parent);
    virtual ~UserAddMoney();
    void goToPrevious(wxCommandEvent &evt);
    void addMoney(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();
};


#endif //CINEMA_USERADDMONEY_H
