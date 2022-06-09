#include "GUI/UserLoginFrame.h"
#include "ServerStuff/functions.h"
#include "GUI/UserPanel.h"

wxBEGIN_EVENT_TABLE(UserLoginFrame,wxFrame)
                EVT_BUTTON(2001, UserLoginFrame::onButtonClicked)
                EVT_BUTTON(80, UserLoginFrame::goBack)
wxEND_EVENT_TABLE()

UserLoginFrame::UserLoginFrame(wxFrame *parent, wxPoint point):MyFrame(parent,1100,"Panel logowania uzytkownia",point,wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX) {
    confirm = new wxButton(this,2001,"Zaloguj sie",wxPoint(475,400),wxSize(250,100));
    wxTextValidator textVal(wxFILTER_EMPTY|wxFILTER_EXCLUDE_CHAR_LIST);
    textVal.SetCharExcludes("&|+/");

    login = new wxTextCtrl(this,2002,"kuba2002",wxPoint(475,240),wxSize(250,50),0,textVal);
    login->SetMaxLength(10);
    password = new wxTextCtrl(this,2003,"lubieprogramowac",wxPoint(475,320),wxSize(250,50),wxTE_PASSWORD,textVal);
    password->SetMaxLength(20);
    description_1 = new wxStaticText(this,62,"Login:",wxPoint(480,225), wxDefaultSize,0);
    description_2 = new wxStaticText(this,63,"Haslo:",wxPoint(480,305), wxDefaultSize,0);

    wxBitmap bitmap(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *button = new wxBitmapButton(this, 80, bitmap, wxPoint(10,10), wxSize(40,40));
}

void UserLoginFrame::onButtonClicked(wxCommandEvent &evt) {
    std::string log = login->GetValue().ToStdString();
    std::string pas = password->GetValue().ToStdString();
    std::vector<std::string> v = exchangeInfoWithServer("clientLogin_",log+"|"+pas);
    if(v[0]!="CanLog")
    {
        wxMessageBox( wxT("Niepoprawne dane."), wxT("Error"), wxICON_INFORMATION);
    } else{
        std::vector<std::string> v = exchangeInfoWithServer("getIdByLogin_",log+"|");
        UserPanel *frame = new UserPanel(this,GetPosition(),CM.getClient(std::stoi(v[0])));
        this->Show(false);
        frame->Show(true);
    }
}

void UserLoginFrame::goBack(wxCommandEvent &evt){
    this->Close(true);
    this->GetParent()->Show(true);
}
