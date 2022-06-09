#include <wx/wx.h>
#include <wx/sizer.h>

#include <wx/wxprec.h>
#include <wx/calctrl.h>
#include <wx/textctrl.h>
#include <wx/statline.h>


class wxCustomDateTimePicker : public wxPanel
{
public:
    wxCustomDateTimePicker();
    explicit wxCustomDateTimePicker(wxWindow* parent,wxWindowID winid);
    virtual ~wxCustomDateTimePicker();
    bool Create(wxWindow *parent,
                wxWindowID id=wxID_ANY,
                wxWindowID winid = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxSize(230,220),
                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                const wxString& name = wxPanelNameStr);
    void onButtonClicked();
public:
    wxButton* confirm;
    wxCalendarCtrl* m_calendar;
};
