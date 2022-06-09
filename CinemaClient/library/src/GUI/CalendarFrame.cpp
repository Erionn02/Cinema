#include "GUI/CalendarFrame.h"
#include "ServerStuff/functions.h"
#include "GUI/RegisterFrame.h"
#include "GUI/MyFrame.h"

wxBEGIN_EVENT_TABLE(CalendarFrame,wxFrame)
    EVT_BUTTON(70,CalendarFrame::onButtonClicked)
    EVT_CALENDAR_SEL_CHANGED(1005,CalendarFrame::changedData)
wxEND_EVENT_TABLE()

CalendarFrame::CalendarFrame(wxFrame *parent,wxTextCtrl* which):MyFrame(parent,2,"RegisterWindow",wxPoint(600,200),wxSize(232,250), wxMINIMIZE_BOX | wxCLOSE_BOX),text(which){

    calendar = new wxCustomDateTimePicker(this,1005);;
    date.Printf(wxT("%s"),wxDateTime::Today().FormatISODate().c_str());
    exchangeInfoWithServer("dummyCall_",date.ToStdString());
    calendar->Show(true);
    confirmDate = new wxButton(this,70,"Zatwierdz",wxPoint(0,172), wxSize(227,50));
}
CalendarFrame::~CalendarFrame() {}
void CalendarFrame::onButtonClicked(wxCommandEvent &evt) {
    //static_cast<RegisterFrame*>(this->GetParent())->birthday->SetValue(date);
    text->SetValue(date);
    this->Close(true);
}

void CalendarFrame::changedData(wxCalendarEvent &evt) {
    date.Printf(wxT("%s"),evt.GetDate().FormatISODate().c_str());
}
