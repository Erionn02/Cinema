//
// Created by student on 27.05.2022.
//

#ifndef INTRODUCTIONPROJECT_MYAPP_H
#define INTRODUCTIONPROJECT_MYAPP_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <GUI/MainFrame.h>


class MyApp : public wxApp
{
private:
    MainFrame* main = nullptr;
public:
    MyApp();

    virtual ~MyApp();

    virtual bool OnInit();
};



//class MyFrame : public wxFrame
//{
//public:
//    MyFrame();
//
//private:
//    void OnHello(wxCommandEvent& event);
//    void OnExit(wxCommandEvent& event);
//    void OnAbout(wxCommandEvent& event);
//};
//
//enum
//{
//    ID_Hello = 1
//};



#endif //INTRODUCTIONPROJECT_MYAPP_H
