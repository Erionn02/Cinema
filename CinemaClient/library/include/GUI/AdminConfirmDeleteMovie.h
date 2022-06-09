//
// Created by student on 05.06.2022.
//

#ifndef CINEMA_ADMINCONFIRMDELETEMOVIE_H
#define CINEMA_ADMINCONFIRMDELETEMOVIE_H
#include "MyFrame.h"

class AdminConfirmDeleteMovie :public MyFrame{
public:
    AdminConfirmDeleteMovie(wxFrame* parent, wxWindowID id);
    virtual ~AdminConfirmDeleteMovie();
    void deleteMovie(wxCommandEvent &evt);
    void doNothing(wxCommandEvent &evt);
private:
    wxButton* confirm;
    wxButton* deny;
    wxStaticText* info;
DECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINCONFIRMDELETEMOVIE_H
