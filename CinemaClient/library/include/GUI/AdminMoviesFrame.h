//
// Created by student on 29.05.2022.
//

#ifndef CINEMA_ADMINMOVIESFRAME_H
#define CINEMA_ADMINMOVIESFRAME_H
#include "MyFrame.h"
#include <wx/wrapsizer.h>
#include <vector>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/vector.h>




class AdminAddMovie;

class AdminMoviesFrame:public MyFrame {
private:
    wxPanel* panel1;
    wxPanel* panel2;
    wxPanel* panel3;
    wxButton * panel1_button;
    wxBitmapButton* goBack;
    wxButton * add_new;
    wxTextCtrl* search;
    wxStaticText* panel2_opis;
    wxFrame* newMovie;
    std::vector<wxCheckBox*> vec;
    wxVector<wxBitmapButton*> buttons_container;
    wxVector<wxStaticText*> text_container;
    wxScrolledWindow* window;

    wxBoxSizer* help_sizer;
    wxFlexGridSizer* movies;

    //dynamic temporary data
    int id=0;
    int free_seats=0;
    int current_movie_id;
    wxScrolledWindow* holder;
    wxGridSizer* seats;
    wxBitmapButton* delete_movie;
    wxStaticText* description;
public:
    AdminMoviesFrame(wxFrame *parent,wxPoint point);

    virtual ~AdminMoviesFrame();
    const int getCurrentMovieId();
    void searchButton(wxCommandEvent &evt);
    void checkBoxes(wxCommandEvent &evt);
    void addNew(wxCommandEvent &evt);
    void goToPrevious(wxCommandEvent &evt);

    void refresh();

    void setMoviesDisplay(std::vector<MoviePtr> objects);
    void clearMoviesDisplay();
    void resize(wxCommandEvent &evt);
    void deleteMovie(wxCommandEvent &evt);

    void updateBarStatus(std::string info);
    DECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINMOVIESFRAME_H
