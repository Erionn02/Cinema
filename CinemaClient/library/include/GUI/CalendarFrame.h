//
// Created by student on 02.06.2022.
//

#ifndef CINEMA_CALENDARFRAME_H
#define CINEMA_CALENDARFRAME_H
#include "RegisterFrame.h"
//#include "AdminAddMovie.h"
#include <wx/wxprec.h>
#include "MyFrame.h"
#include "Calendar.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class CalendarFrame: public MyFrame{
public:
wxDECLARE_EVENT_TABLE();
public://oddzielone pola klasy od metod
    CalendarFrame(wxFrame* parent,wxTextCtrl* which);
    void onButtonClicked(wxCommandEvent &evt);
    virtual ~CalendarFrame();
    void changedData(wxCalendarEvent &evt);

    wxTextCtrl *text;
    wxString date;
    wxButton *confirmDate=nullptr;
    wxCustomDateTimePicker* calendar=nullptr;
};




#endif //CINEMA_CALENDARFRAME_H
