//
// Created by student on 29.05.2022.
//

#ifndef CINEMA_USERPANEL_H
#define CINEMA_USERPANEL_H
#include "MyFrame.h"
class UserPanel:public MyFrame {
private:
    ClientPtr thisClient;
    wxPanel* panel1;
    wxPanel* panel2;
    wxButton * panel1_button;

    wxBitmapButton* moneyButton;
    wxBitmapButton* goBack;
    wxBitmapButton* unregisterButton;

    wxTextCtrl* search;
    wxStaticText* panel2_opis;
    wxFrame* newMovie;
    std::vector<wxCheckBox*> vec;
    wxVector<wxBitmapButton*> buttons_container;
    wxVector<wxStaticText*> text_container;
    wxScrolledWindow* window;
    wxScrolledWindow* ticketsWindow;
    wxFlexGridSizer* tickets;

    wxBoxSizer* help_sizer;
    wxFlexGridSizer* movies;

    //search 2
    wxButton* search2;
    wxStaticText* description2;
    wxTextCtrl* searchTickets;
    wxStaticBox* panel3box;
    wxVector<wxCheckBox*> vec2;
    wxStaticText* briefUserInfo;

    //dynamic temporary data
    int id=0;
    int free_seats=0;
    int current_movie_id;
    wxScrolledWindow* holder;
    wxGridSizer* seats;
    wxBitmapButton* buyButton;
    wxStaticText* description;
    wxButton* previous_seat=nullptr;
public:
    UserPanel(wxFrame* parent,wxPoint point,ClientPtr thisClient);

    virtual ~UserPanel();

    const ClientPtr &getThisClient() const;

    wxButton *getPreviousSeat() const;

    const int getCurrentMovieId();
    void searchButtonMovies(wxCommandEvent &evt);
    void searchButtonTickets(wxCommandEvent &evt);
    void checkBoxesMovies(wxCommandEvent &evt);
    void checkBoxesTickets(wxCommandEvent &evt);
    void addNew(wxCommandEvent &evt);
    void unregister(wxCommandEvent &evt);
    void updateClientInfo();
    void addMoneyToBalance(wxCommandEvent &evt);

    void goToPrevious(wxCommandEvent &evt);

    void refreshMovies();
    void refreshTickets();

    void setTicketsDisplay(std::vector<TicketPtr> tickets);
    void setMoviesDisplay(std::vector<MoviePtr> objects);
    void clearMoviesDisplay();
    void clearTicketsDisplay();
    void resize(wxCommandEvent &evt);
    void deleteMovie(wxCommandEvent &evt);

    void updateBarStatus(std::string info);
    void updateSeat(wxCommandEvent &evt);
    void buyTicket(wxCommandEvent &evt);
DECLARE_EVENT_TABLE();
};


#endif //CINEMA_USERPANEL_H
