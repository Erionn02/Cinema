//
// Created by student on 29.05.2022.
//

#ifndef CINEMA_ADMINUSERSFRAME_H
#define CINEMA_ADMINUSERSFRAME_H
#include "MyFrame.h"
class AdminUsersFrame:public MyFrame {
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
    wxFlexGridSizer* users;

    int id=0;
    int current_user_id;
    wxScrolledWindow* holder;
    //wxGridSizer* seats;
    wxBitmapButton* unregisterUser;
    wxStaticText* description;
public:
    AdminUsersFrame(wxFrame *parent,wxPoint point);

    virtual ~AdminUsersFrame();
    void searchButton(wxCommandEvent &evt);
    void checkBoxes(wxCommandEvent &evt);
    void addNew(wxCommandEvent &evt);
    void goToPrevious(wxCommandEvent &evt);

    void setUsersDisplay(std::vector<ClientPtr> objects);
    void clearUsersDisplay();
    void resize(wxCommandEvent &evt);
    void deleteUser(wxCommandEvent &evt);
    void refresh();
    const int getCurrentUserId();
    void updateBarStatus(std::string info);
DECLARE_EVENT_TABLE();

};


#endif //CINEMA_ADMINUSERSFRAME_H
