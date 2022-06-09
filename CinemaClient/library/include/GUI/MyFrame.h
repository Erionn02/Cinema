//
// Created by student on 28.05.2022.
//

#ifndef INTRODUCTIONPROJECT_MYFRAME_H
#define INTRODUCTIONPROJECT_MYFRAME_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "managers/MovieManager.h"
#include "managers/ClientManager.h"
#include "managers/ScreeningRoomManager.h"


class MyFrame :public wxFrame{
public:
    ///współdzielone dane w każdym z okien
    static MovieManager MM;
    static ClientManager CM;
    static ScreeningRoomManager SRM;
    //wiem że dwukrotne pisanie public w taki sposób nie jest konieczne,
    //służy jedynie aby był wydoczny podział pól i metod klasy
public:
    MyFrame(wxWindow *parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE,
            const wxString& name = wxASCII_STR(wxFrameNameStr));
    virtual ~MyFrame();
};


#endif //INTRODUCTIONPROJECT_MYFRAME_H
