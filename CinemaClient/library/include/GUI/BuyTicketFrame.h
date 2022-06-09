//
// Created by student on 06.06.2022.
//

#ifndef CINEMA_BUYTICKETFRAME_H
#define CINEMA_BUYTICKETFRAME_H
#include "MyFrame.h"

class BuyTicketFrame:public MyFrame {
private:
    wxButton* confirm;
    wxButton* deny;
    wxStaticText* info;
    wxStaticText* moneyInfo;
    MoviePtr movie;
    ClientPtr client;
public:
    BuyTicketFrame(wxFrame* parent, wxWindowID id);
    virtual ~BuyTicketFrame();
    void buyTicket(wxCommandEvent &evt);
    void doNothing(wxCommandEvent &evt);
DECLARE_EVENT_TABLE();
};


#endif //CINEMA_BUYTICKETFRAME_H
