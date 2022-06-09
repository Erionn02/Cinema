//
// Created by student on 05.06.2022.
//

#include "GUI/AdminConfirmDeleteMovie.h"
#include "ServerStuff/functions.h"
#include "GUI/AdminMoviesFrame.h"
#include "model/ScreeningRoom.h"
#include "model/Movie.h"

wxBEGIN_EVENT_TABLE(AdminConfirmDeleteMovie,wxFrame)
                EVT_BUTTON(1301, AdminConfirmDeleteMovie::deleteMovie)
                EVT_BUTTON(1302,AdminConfirmDeleteMovie::doNothing)
wxEND_EVENT_TABLE()

AdminConfirmDeleteMovie::~AdminConfirmDeleteMovie() {

}
AdminConfirmDeleteMovie::AdminConfirmDeleteMovie(wxFrame *parent,wxWindowID id) : MyFrame(parent,id,"Dodawanie nowego filmu",wxPoint(750,290),wxSize(375,250),wxMINIMIZE_BOX | wxCLOSE_BOX)
{
    info = new wxStaticText(this,1300,"Czy na pewno chcesz usunac film?",wxPoint(20,10));
    confirm = new wxButton(this,1301,"TAK",wxPoint(10,70),wxSize(170,150));
    deny = new wxButton(this,1302,"NIE",wxPoint(190,70),wxSize(170,150));
}

void AdminConfirmDeleteMovie::deleteMovie(wxCommandEvent &evt) {
    int id = static_cast<AdminMoviesFrame*>(this->GetParent())->getCurrentMovieId();
    MoviePtr tmp = MM.getMovie(id);
    MM.endMovie(tmp);
    std::string parsed_movie = convertMovieToStr(tmp);
    exchangeInfoWithServer("endMovie_",parsed_movie);
    std::string parsed_updated_room = convertScreeningRoomToStr(tmp->getScreeningRoom());
    exchangeInfoWithServer("updateScreeningRoom_",parsed_updated_room);
    static_cast<AdminMoviesFrame*>(this->GetParent())->refresh();
    static_cast<AdminMoviesFrame*>(this->GetParent())->updateBarStatus("Ilosc senasow: "+std::to_string(MM.getSize()));
    this->Close();
}

void AdminConfirmDeleteMovie::doNothing(wxCommandEvent &evt) {
    this->Close();
}
