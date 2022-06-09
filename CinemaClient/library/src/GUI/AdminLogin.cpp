
#include "GUI/AdminLogin.h"
#include "ServerStuff/functions.h"
#include "GUI/AdminPanel.h"

wxBEGIN_EVENT_TABLE(AdminLogin,wxFrame)
                EVT_BUTTON(2001, AdminLogin::onButtonClicked)
                EVT_BUTTON(80, AdminLogin::goBack)
wxEND_EVENT_TABLE()

AdminLogin::~AdminLogin() {

}

AdminLogin::AdminLogin(wxFrame* parent, wxPoint point):MyFrame(parent,2000,"Panel logowania administratora",point,wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX) {
    confirm = new wxButton(this,2001,"Zaloguj sie",wxPoint(475,400),wxSize(250,100));
    wxTextValidator textVal(wxFILTER_EMPTY|wxFILTER_EXCLUDE_CHAR_LIST);
    textVal.SetCharExcludes("&|+/");
    login = new wxTextCtrl(this,2002,"root",wxPoint(475,240),wxSize(250,50),0,textVal);
    login->SetMaxLength(10);
    password = new wxTextCtrl(this,2003,"root",wxPoint(475,320),wxSize(250,50),wxTE_PASSWORD,textVal);
    password->SetMaxLength(20);

    description_1 = new wxStaticText(this,62,"Login:",wxPoint(480,225), wxDefaultSize,0);
    description_2 = new wxStaticText(this,63,"Haslo:",wxPoint(480,305), wxDefaultSize,0);

    wxBitmap bitmap(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *button = new wxBitmapButton(this, 80, bitmap, wxPoint(10,10), wxSize(40,40));
}

void AdminLogin::onButtonClicked(wxCommandEvent &evt) {
    std::string log = login->GetValue().ToStdString();
    std::string pas = password->GetValue().ToStdString();
    std::vector<std::string> v = exchangeInfoWithServer("adminLogin_",log+"|"+pas);
    if(v[0]!="CanLog")
    {
        wxMessageBox( wxT("Niepoprawne dane."), wxT("Error"), wxICON_INFORMATION);
    } else{
        AdminPanel *a = new AdminPanel(this,GetPosition());

        this->Show(false);
        a->Show(true);
    }
}
void AdminLogin::goBack(wxCommandEvent &evt){
    this->GetParent()->Show(true);
    this->GetParent()->SetPosition(this->GetPosition());
    this->Close(true);
}