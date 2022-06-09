#ifndef INTRODUCTIONPROJECT_REGISTERFRAME_H
#define INTRODUCTIONPROJECT_REGISTERFRAME_H

#include <wx/wxprec.h>
#include "MyFrame.h"
#include <wx/timectrl.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class AdminAddMovie: public MyFrame{
private:
    wxTextCtrl* title;
    wxTextCtrl* type;
    wxTextCtrl* time;
    wxTextCtrl* ageRequired;
    wxTextCtrl* price;
    wxTextCtrl* room;
    wxTextCtrl* data;
    wxTextCtrl* hour;
    wxButton* confirm;
    wxButton* choose_date;
    wxStaticBox* box_1;
    wxTimePickerCtrl* date;
    double price_num;
public:
    AdminAddMovie(wxFrame* parent,wxWindowID id);
    virtual ~AdminAddMovie();
    void confirmButton(wxCommandEvent &evt);
    void chooseDate(wxCommandEvent &evt);
    void goBack(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINADDMOVIE_H
