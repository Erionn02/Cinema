#include "GUI/Calendar.h"
wxCustomDateTimePicker::wxCustomDateTimePicker(wxWindow* parent,wxWindowID winid)
{
    Create(parent,winid);
}

wxCustomDateTimePicker::wxCustomDateTimePicker(){}

bool wxCustomDateTimePicker::Create(wxWindow *parent, wxWindowID id,wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool res = wxPanel::Create(parent, winid, pos, size, style, name);

    SetBackgroundColour(parent->GetBackgroundColour());
    //SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetForegroundColour(parent->GetForegroundColour());

    m_calendar = new wxCalendarCtrl(this, id, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER | wxCAL_SEQUENTIAL_MONTH_SELECTION );
    wxPoint pt(m_calendar->GetPosition());

    //pt.y += m_calendar->GetSize().GetHeight() + 5;
    wxStaticLine* line = new wxStaticLine(this, wxID_ANY, pt, wxSize(m_calendar->GetSize().GetWidth(), 2));
    //pt.y += 6;
    //m_timeText = new wxTextCtrl(this, wxID_ANY, wxT("12:34:56"), pt);
    return res;
}

wxCustomDateTimePicker::~wxCustomDateTimePicker(){}

void wxCustomDateTimePicker::onButtonClicked() {

}