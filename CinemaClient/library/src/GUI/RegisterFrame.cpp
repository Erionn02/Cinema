//
// Created by student on 27.05.2022.
//

#include "GUI/RegisterFrame.h"
#include "ServerStuff/functions.h"
#include "typedefs.h"
#include "model/Client.h"
#include "GUI/MyFrame.h"
#include "Exceptions/CinemaException.h"
#include "GUI/CalendarFrame.h"


wxBEGIN_EVENT_TABLE(RegisterFrame,wxFrame)
                EVT_BUTTON(57, RegisterFrame::onButtonClicked)
                EVT_BUTTON(61, RegisterFrame::onButtonClickDate)
                EVT_BUTTON(80, RegisterFrame::goBack)
wxEND_EVENT_TABLE()


RegisterFrame::RegisterFrame(wxFrame* parent, wxPoint pos):MyFrame(parent,2,"RegisterWindow",pos,wxSize(1200,800), wxMINIMIZE_BOX | wxCLOSE_BOX) {
    wxTextValidator textVal(wxFILTER_EMPTY|wxFILTER_EXCLUDE_CHAR_LIST);
    textVal.SetCharExcludes("&|+/");
    login = new wxTextCtrl(this,50,"",wxPoint(350,310),wxSize(200,50),0,textVal);
    login->SetMaxLength(10);
    password = new wxTextCtrl(this,51,"",wxPoint(350,390),wxSize(200,50),wxTE_PASSWORD,textVal);
    password->SetMaxLength(20);
    password_confirm = new wxTextCtrl(this,52,"",wxPoint(350,470),wxSize(200,50),wxTE_PASSWORD,textVal);
    password_confirm->SetMaxLength(20);
    email = new wxTextCtrl(this,53,"",wxPoint(650,470),wxSize(200,50),0,textVal);
    email->SetMaxLength(35);
    name = new wxTextCtrl(this,54,"",wxPoint(650,310),wxSize(200,50),0,textVal);
    name->SetMaxLength(25);
    surname = new wxTextCtrl(this,55,"",wxPoint(650,390),wxSize(200,50),0,textVal);
    surname->SetMaxLength(25);
    wxTextValidator textVal2(wxFILTER_EMPTY|wxFILTER_INCLUDE_CHAR_LIST);
    textVal2.SetCharIncludes("01234567890-");
    birthday = new wxTextCtrl(this,56,"RR-MM-DD",wxPoint(650,550),wxSize(200,50),0,textVal2);
    birthday->SetMaxLength(10);
    birthday->SetEditable(false);

    confirm = new wxButton(this,57,"Zarejestruj sie",wxPoint(400,680),wxSize(400,50));
    box1 = new wxStaticBox(this, 61,"", wxPoint(344, 47), wxSize(520, 230));
    window1 = new wxStaticText(this,59, "UTWORZ SWOJE KONTO \n I ZAMAWIAJ BILETY BEZ \n WYCHODZENIA Z DOMU", wxPoint(440, 70), wxSize(500,200), 0);
    window1->SetFont(window1->GetFont().Scale(2.0));
    window2 = new wxStaticText(this,60, "WPISZ WYMAGANE DANE", wxPoint(480, 220), wxSize(520,200), 0);
    window2->SetFont(window2->GetFont().Scale(1.5));
    choose_date = new wxButton(this,61, "Wybierz date", wxPoint(350,550), wxSize(200,50));

    description_1 = new wxStaticText(this,62,"Login:",wxPoint(355,295), wxDefaultSize,0);
    description_2 = new wxStaticText(this,63,"Haslo:",wxPoint(355,375), wxDefaultSize,0);
    description_3 = new wxStaticText(this,64,"Potwierdz haslo:",wxPoint(355,455), wxDefaultSize,0);
    description_4 = new wxStaticText(this,65,"Imie:",wxPoint(655,295), wxDefaultSize,0);
    description_5 = new wxStaticText(this,66,"Nazwisko:",wxPoint(655,375), wxDefaultSize,0);
    description_6 = new wxStaticText(this,67,"E-mail:",wxPoint(655,455), wxDefaultSize,0);

    wxBitmap bitmap(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *button = new wxBitmapButton(this, 80, bitmap, wxPoint(10,10), wxSize(40,40));

}

void RegisterFrame::onButtonClicked(wxCommandEvent &evt) {
    std::string log = login->GetValue().ToStdString();
    std::string pas = password->GetValue().ToStdString();
    std::string pas_confirm = password_confirm->GetValue().ToStdString();
    std::string nam = name->GetValue().ToStdString();
    std::string lastName = surname->GetValue().ToStdString();
    std::string emai = email->GetValue().ToStdString();
    std::string date = birthday->GetValue().ToStdString();

    std::vector<std::string> v = exchangeInfoWithServer("checkLoginAndMail_",log+"|"+emai);
    if(v[0]=="1")wxMessageBox( wxT("This login or email is already in use."), wxT("Error"), wxICON_INFORMATION);
    else {
        try {
            if(pas_confirm!=pas)throw CinemaException("Hasla musza byc takie same!");
            if(pas.length()<8)throw CinemaException("Haslo musi miec minimum 8 znakow");
            int id = getID();
            pt::ptime data = convertStringToDate(date);
            ClientPtr c = CM.registerClient(nam, lastName, data, id, 0.0);
            exchangeInfoWithServer("registeruser_", log+"|"+pas+"|"+emai+"|"+convertClientToStr(c));
            exchangeInfoWithServer("dummyCall_", log+"|"+pas+"|"+emai+"|"+convertClientToStr(c));
            wxMessageBox( wxString("Konto utworzone!"), wxT("Rejestracja"), wxICON_INFORMATION);
            this->GetParent()->Show(true);
            this->GetParent()->SetPosition(this->GetPosition());
            this->Close(true);
        }
        catch(CinemaException &e)
        {
            wxMessageBox( wxString(e.what()), wxT("Error"), wxICON_INFORMATION);
        }
        catch(std::exception &e)
        {
            wxMessageBox( wxString(e.what()), wxT("Error"), wxICON_INFORMATION);
        }
    }
}

RegisterFrame::~RegisterFrame() {

}

void RegisterFrame::onButtonClickDate(wxCommandEvent &evt){
    CalendarFrame *calendar = new CalendarFrame (this,birthday);
    calendar->Show(true);
}

void RegisterFrame::goBack(wxCommandEvent &evt){
    this->GetParent()->Show(true);
    this->GetParent()->SetPosition(this->GetPosition());
    this->Close(true);
}