//
// Created by student on 29.05.2022.
//

#ifndef CINEMA_ADMINROOMSFRAME_H
#define CINEMA_ADMINROOMSFRAME_H
#include "MyFrame.h"
#include <wx/wrapsizer.h>
#include <vector>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/vector.h>

class AdminRoomsFrame:public MyFrame {
private:
    wxBitmapButton* goBack;
    wxPanel* panel1;
    wxPanel* panel2;
    wxButton * panel1_button;
    wxButton * add_new;
    wxTextCtrl* search;
    wxStaticText* panel2_opis;
    wxFrame * newRoom;
    std::vector<wxCheckBox*> vec;
    wxVector<wxBitmapButton*> buttons_container;
    wxVector<wxStaticText*> text_container;
    wxScrolledWindow* window;

    wxBoxSizer* help_sizer;
    wxFlexGridSizer* rooms;

    int id=0;
    int current_room_id;
    wxScrolledWindow* holder;
    wxGridSizer* seats;
    wxBitmapButton* delete_movie;
    wxStaticText* description;

public:
    AdminRoomsFrame(wxFrame *parent,wxPoint point);
    virtual ~AdminRoomsFrame();

    void searchButton(wxCommandEvent &evt);
    void checkBoxes(wxCommandEvent &evt);
    void addNew(wxCommandEvent &evt);
    void goToPrevious(wxCommandEvent &evt);

    void setRoomsDisplay(std::vector<ScreeningRoomPtr> objects);
    void clearRoomsDisplay();
    void resize(wxCommandEvent &evt);
    void deleteRoom(wxCommandEvent &evt);
    void refresh();
    const int getCurrentRoomId();
    void updateBarStatus(std::string info);
    DECLARE_EVENT_TABLE();
};


#endif //CINEMA_ADMINROOMSFRAME_H
