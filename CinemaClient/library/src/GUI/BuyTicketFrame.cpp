//
// Created by student on 06.06.2022.
//

#include "GUI/BuyTicketFrame.h"
#include "GUI/UserPanel.h"
#include "model/Movie.h"
#include "model/Client.h"
#include "model/Ticket.h"
#include "ServerStuff/functions.h"
wxBEGIN_EVENT_TABLE(BuyTicketFrame,wxFrame)
                EVT_BUTTON(1301, BuyTicketFrame::buyTicket)
                EVT_BUTTON(1302,BuyTicketFrame::doNothing)
wxEND_EVENT_TABLE()

BuyTicketFrame::BuyTicketFrame(wxFrame *parent,wxWindowID id) : MyFrame(parent,id,"Dodawanie nowego filmu",wxPoint(750,290),wxSize(375,450),wxMINIMIZE_BOX | wxCLOSE_BOX)
{
    int idOfMovie = static_cast<UserPanel*>(this->GetParent())->getCurrentMovieId();
    client = static_cast<UserPanel*>(this->GetParent())->getThisClient();
    movie= MM.getMovie(idOfMovie);
    int price = movie->getPrice();
    info = new wxStaticText(this,1300,"Czy na pewno chcesz kupic bilet na film "+movie->getTitle(),wxPoint(5,10),wxDefaultSize);
    info = new wxStaticText(this,wxID_ANY,"Cena biletu: "+std::to_string(price)+"\n po znizkach: "+std::to_string(client->getRealPrice(price))+"\nStan konta: "+std::to_string(client->getBalance()),wxPoint(20,60));
    confirm = new wxButton(this,1301,"TAK",wxPoint(10,270),wxSize(170,150));
    deny = new wxButton(this,1302,"NIE",wxPoint(190,270),wxSize(170,150));
}

BuyTicketFrame::~BuyTicketFrame() {

}

void BuyTicketFrame::buyTicket(wxCommandEvent &evt) {
    double balance=client->getBalance();
    double price = client->getRealPrice(movie->getPrice());
    if(balance<price)
    {
        wxMessageBox( wxString("Zbyt malo srodkow na koncie."), wxT("Error"), wxICON_INFORMATION);
    }
    else
    {
        try {
            if(static_cast<UserPanel*>(this->GetParent())->getPreviousSeat()==nullptr)throw CinemaException("Miejsce nie jest wybrane");
            std::string info = static_cast<UserPanel*>(this->GetParent())->getPreviousSeat()->GetLabel().ToStdString();
            std::vector<std::string> v = split(info,"-");
            CM.buyMovieTicket(client,movie,convertNumToSegment(std::stoi(v[0])), std::stoi(v[1]));
            std::string parsed_client = convertClientToStr(client);
            exchangeInfoWithServer("changeActiveUserState_",parsed_client);
            exchangeInfoWithServer("updateScreeningRoom_",convertScreeningRoomToStr(movie->getScreeningRoom()));
            static_cast<UserPanel*>(this->GetParent())->refreshTickets();
            static_cast<UserPanel*>(this->GetParent())->refreshMovies();
            static_cast<UserPanel*>(this->GetParent())->updateClientInfo();
            this->Close(true);
        }
        catch(CinemaException &e)
        {
            wxMessageBox( wxString(e.what()), wxT("Error"), wxICON_INFORMATION);
        }
    }
}

void BuyTicketFrame::doNothing(wxCommandEvent &evt) {
    this->Close(true);
}
