//
// Created by student on 27.05.2022.
//

#ifndef INTRODUCTIONPROJECT_REGISTERFRAME_H
#define INTRODUCTIONPROJECT_REGISTERFRAME_H

#include <wx/wxprec.h>
#include "MyFrame.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class RegisterFrame :public MyFrame{
private:
    wxTextCtrl* login;
    wxTextCtrl* password;
    wxTextCtrl* password_confirm;
    wxTextCtrl* email;
    wxTextCtrl* name;
    wxTextCtrl* surname;
    wxTextCtrl* birthday;
    wxButton* confirm;
    wxStaticText* window1;
    wxStaticText* window2;
    wxStaticBox* box1;
    wxButton* choose_date;
    wxStaticText* description_1;
    wxStaticText* description_2;
    wxStaticText* description_3;
    wxStaticText* description_4;
    wxStaticText* description_5;
    wxStaticText* description_6;
public:
    RegisterFrame(wxFrame* parent,wxPoint pos);
    void onButtonClicked(wxCommandEvent &evt);
    void onButtonClickDate(wxCommandEvent &evt);
    void goBack(wxCommandEvent &evt);
    virtual ~RegisterFrame();
wxDECLARE_EVENT_TABLE();
};


#endif //INTRODUCTIONPROJECT_REGISTERFRAME_H
