//
// Created by student on 27.05.2022.
//

#ifndef INTRODUCTIONPROJECT_MAINFRAME_H
#define INTRODUCTIONPROJECT_MAINFRAME_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "managers/MovieManager.h"
#include "managers/ClientManager.h"
#include "managers/ScreeningRoomManager.h"
#include "MyFrame.h"

class MainFrame : public MyFrame{
    wxButton *registerButton;
    wxButton *adminButton;
    wxButton *loginButton;
public:
    MainFrame();
    void onButtonClickedRegister(wxCommandEvent &evt);
    void onButtonClickedAdmin(wxCommandEvent &evt);
    void onButtonClickedLogin(wxCommandEvent &evt);
    virtual ~MainFrame();
wxDECLARE_EVENT_TABLE();
};


#endif //INTRODUCTIONPROJECT_MAINFRAME_H
