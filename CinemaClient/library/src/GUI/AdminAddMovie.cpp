//
// Created by student on 03.06.2022.
//

#include "GUI/AdminAddMovie.h"
#include <wx/valnum.h>
#include "GUI/CalendarFrame.h"
#include "ServerStuff/functions.h"
#include "Exceptions/CinemaException.h"
#include <exception>
#include "GUI/AdminMoviesFrame.h"
AdminAddMovie::~AdminAddMovie() {

}
wxBEGIN_EVENT_TABLE(AdminAddMovie,wxFrame)
                EVT_BUTTON(57, AdminAddMovie::confirmButton)
                EVT_BUTTON(70, AdminAddMovie::chooseDate)
                EVT_BUTTON(80, AdminAddMovie::goBack)
wxEND_EVENT_TABLE()

AdminAddMovie::AdminAddMovie(wxFrame *parent,wxWindowID id) : MyFrame(parent,id,"Dodawanie nowego filmu",wxPoint(700,200),wxSize(500,800),wxMINIMIZE_BOX | wxCLOSE_BOX){
    exchangeInfoWithServer("dummyCall_",MM.getMoviesInfo());
    wxTextValidator textVal(wxFILTER_EMPTY|wxFILTER_EXCLUDE_CHAR_LIST);
    textVal.SetCharExcludes("&|+/-()#");

    title = new wxTextCtrl(this,50,"",wxPoint(20,250),wxSize(200,50),0,textVal);
    title->SetMaxLength(20);

    type = new wxTextCtrl(this,53,"",wxPoint(20,320),wxSize(200,50),0,textVal);
    type->SetMaxLength(35);

    wxTextValidator textVal2(wxFILTER_EMPTY|wxFILTER_DIGITS);
    ageRequired = new wxTextCtrl(this,54,"",wxPoint(20,390),wxSize(200,50),0,textVal2);
    ageRequired->SetMaxLength(2);

    wxFloatingPointValidator<double> val(2, &price_num, wxNUM_VAL_ZERO_AS_BLANK);
    val.SetRange(0, 9999);
    data = new wxTextCtrl(this,56,"RR-MM-DD",wxPoint(20,460),wxSize(200,50),0,textVal2);
    data->SetMaxLength(40);
    data->SetEditable(false);

    price = new wxTextCtrl(this,57,"", wxPoint(270,250), wxSize(200,50),0,val);
    price->SetMaxLength(6);

    room = new wxTextCtrl(this,58,"", wxPoint(270,320), wxSize(200,50),0,textVal2);
    room->SetMaxLength(7);

    date = new wxTimePickerCtrl(this,1111,wxDefaultDateTime,wxPoint(270,465));

    time = new wxTextCtrl(this,60,"", wxPoint(270,390), wxSize(200,50));

    choose_date = new wxButton(this,70,"Wybierz date",wxPoint(20,600), wxSize(200,50));
    confirm = new wxButton(this,57,"Dodaj film",wxPoint(270,600),wxSize(200,50));
    //confirm->SetOwnBackgroundColour(wxColour(200,200,300));
    box_1 = new wxStaticBox(this, 61,"", wxPoint(5, 5), wxSize(483, 200));
    //box_1->SetOwnBackgroundColour(wxColour(235,64,52)); //nie moglem sie powstrzymac ;)
    wxStaticText* info = new wxStaticText(this,602,"UTWORZ NOWY SEANS",wxPoint(50,70),wxSize(450,250));
    info->SetFont(info->GetFont().Scale(2.5));

    wxStaticText* description_1 = new wxStaticText(this,62,"Tytul filmu:",wxPoint(25,235), wxDefaultSize,0);
    wxStaticText* description_2 = new wxStaticText(this,63,"Rodziaj filmu::",wxPoint(25,305), wxDefaultSize,0);
    wxStaticText* description_3 = new wxStaticText(this,64,"Wymagany wiek:",wxPoint(25,375), wxDefaultSize,0);
    wxStaticText* description_4 = new wxStaticText(this,65,"Data:",wxPoint(25,445), wxDefaultSize,0);
    wxStaticText* description_5 = new wxStaticText(this,66,"Cena:",wxPoint(275,235), wxDefaultSize,0);
    wxStaticText* description_6 = new wxStaticText(this,67,"ID Sali kinowej:",wxPoint(275,305), wxDefaultSize,0);
    wxStaticText* description_7 = new wxStaticText(this,68,"Godzina:",wxPoint(275,445), wxDefaultSize,0);
    wxStaticText* description_8 = new wxStaticText(this,69,"Czas trwania w minutach:",wxPoint(275,375), wxDefaultSize,0);

    wxBitmap bitmap(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *button = new wxBitmapButton(this, 80, bitmap, wxPoint(10,10), wxSize(40,40));

}

void AdminAddMovie::confirmButton(wxCommandEvent &evt) {
    if(time->GetValue().ToStdString()!="RR-MM-DD") {
        try {
            std::string title_str = title->GetValue().ToStdString();
            std::string type_str = type->GetValue().ToStdString();
            if(ageRequired->GetValue().ToStdString().length()==0)throw std::logic_error("Minimalny wiek musi byc ustawiony");
            if(price->GetValue().ToStdString().length()==0)throw std::logic_error("Cena musi byc ustawiona");
            if(room->GetValue().ToStdString().length()==0)throw std::logic_error("ID sali musi byc ustawione");
            int age = std::stoi(ageRequired->GetValue().ToStdString());
            double price_movie = std::stod(price->GetValue().ToStdString());
            ScreeningRoomPtr sRoom = SRM.findById(std::stoi(room->GetValue().ToStdString()));
            if(!sRoom)throw std::logic_error("nullptr");
            pt::ptime start_time = convertStringToDate(data->GetValue().ToStdString());

            std::vector<std::string> parsed_hour = split(date->GetValue().FormatISOTime().ToStdString(),":");
            start_time+=pt::hours(std::stoi(parsed_hour[0]))+pt::minutes(std::stoi(parsed_hour[1]))+pt::seconds(std::stoi(parsed_hour[2]));
            int duration = std::stoi(time->GetValue().ToStdString());
            std::vector<std::string> id = exchangeInfoWithServer("getID_","");
            MoviePtr m =MM.addMovie(std::stoi(id[0]),title_str,start_time,duration,age,type_str,sRoom,price_movie);
            std::string parsed_movie = convertMovieToStr(m);
            exchangeInfoWithServer("registerMovie_",parsed_movie);
            wxMessageBox( wxString("Film pomyslnie utworony!"), wxT("Nowy film"), wxICON_INFORMATION);
            int num = MM.getSize();
            static_cast<AdminMoviesFrame*>(this->GetParent())->updateBarStatus("Ilosc seansow: "+std::to_string(num));
            static_cast<AdminMoviesFrame*>(this->GetParent())->refresh();
            this->Close(true);
        }
        catch (CinemaException &e) {
            wxMessageBox( wxString(e.what()), wxT("Error"), wxICON_INFORMATION);
        }
        catch(std::exception &e)
        {
            wxMessageBox( wxString(e.what()), wxT("Error"), wxICON_INFORMATION);
        }
    }
    else
    {
        wxMessageBox( wxString("Nalezy wybrac date"), wxT("Error"), wxICON_INFORMATION);
    }
}

void AdminAddMovie::chooseDate(wxCommandEvent &evt) {
    CalendarFrame *calendar = new CalendarFrame (this,data);
    calendar->Show(true);
}

void AdminAddMovie::goBack(wxCommandEvent &evt) {
    this->Close(true);
    this->GetParent()->Show(true);
}


