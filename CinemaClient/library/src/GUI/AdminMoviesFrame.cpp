//
// Created by student on 29.05.2022.
//
#include "GUI/AdminMoviesFrame.h"
#include "ServerStuff/functions.h"
#include "GUI/AdminAddMovie.h"
#include "GUI/AdminConfirmDeleteMovie.h"
#include "stdlib.h"
#include "time.h"
#include <wx/scrolwin.h>
#include "model/Movie.h"
#include "model/ScreeningRoom.h"
#include "typedefs.h"
#include <boost/algorithm/string.hpp>
wxBEGIN_EVENT_TABLE(AdminMoviesFrame,wxFrame)
                EVT_BUTTON(1001, AdminMoviesFrame::searchButton)

                EVT_CHECKBOX(1005,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1006,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1007,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1008,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1009,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1010,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1011,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1012,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1013,AdminMoviesFrame::checkBoxes)
                EVT_CHECKBOX(1014,AdminMoviesFrame::checkBoxes)

                EVT_BUTTON(1022,AdminMoviesFrame::addNew)
                EVT_BUTTON(1024,AdminMoviesFrame::goToPrevious)

                EVT_BUTTON(1245,AdminMoviesFrame::deleteMovie)
wxEND_EVENT_TABLE()

AdminMoviesFrame::AdminMoviesFrame(wxFrame *parent, wxPoint point):MyFrame(parent,900,"Panel zarzadzania filmami",point,wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX) {

    panel1 = new wxPanel(this,1,wxPoint(10,1),wxSize(900,200));
    wxStaticBox* panel1_box = new wxStaticBox(this,1000,"",panel1->GetPosition(),panel1->GetSize());
    wxStaticText* panel1_opis = new wxStaticText(panel1,1003,"Wyszukaj filmy po zadanym kryterium:",wxPoint(30,30));
    search = new wxTextCtrl(panel1,1002,"",wxPoint(30,60),wxSize(600,50));
    panel1_button = new wxButton(panel1,1001,"Szukaj",wxPoint(630,60),wxSize(200,50));

    wxCheckBox* box1 = new wxCheckBox(panel1,1005,wxString("Wszystkie"),wxPoint(30,140));
    wxCheckBox* box2 = new wxCheckBox(panel1,1006,wxString("Tytul"),wxPoint(165,140));
    wxCheckBox* box3 = new wxCheckBox(panel1,1007,wxString("ID"),wxPoint(260,140));
    wxCheckBox* box4 = new wxCheckBox(panel1,1008,wxString("W okolicach daty [RR-MM-DD]"),wxPoint(310,140));
    wxCheckBox* box5 = new wxCheckBox(panel1,1009,wxString("Wiek conajmniej"),wxPoint(550,140));
    wxCheckBox* box6 = new wxCheckBox(panel1,1010,wxString("Cena nie wiecej niz"),wxPoint(700,140));
    wxCheckBox* box7 = new wxCheckBox(panel1,1011,wxString("W sali kinowej o ID"),wxPoint(30,170));
    wxCheckBox* box8 = new wxCheckBox(panel1,1012,wxString("Typ filmu"),wxPoint(210,170));
    wxCheckBox* box9 = new wxCheckBox(panel1,1013,wxString("Maksymalny wymagany wiek"),wxPoint(320,170));
    wxCheckBox* box10 = new wxCheckBox(panel1,1014,wxString("Minimalnie wykupionych biletow na film"),wxPoint(560,170));
    vec.push_back(box1);
    vec.push_back(box2);
    vec.push_back(box3);
    vec.push_back(box4);
    vec.push_back(box5);
    vec.push_back(box6);
    vec.push_back(box7);
    vec.push_back(box8);
    vec.push_back(box9);
    vec.push_back(box10);
    box1->SetValue(true);


    //panel2

    panel2 = new wxPanel(this,205,wxPoint(910,1),wxSize(190,200));
    int num = MM.getSize();
    panel2_opis = new wxStaticText(this,1021,"Ilosc seansow: "+std::to_string(num),wxPoint(920,30));
    wxStaticBox* panel2_box = new wxStaticBox(this,1020,"",wxPoint(910,1),wxSize(275,200));
    add_new = new wxButton(this,1022,"Dodaj nowy",wxPoint(920,50),wxSize(255,140));
    wxBitmap bitmap_2(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *goBack = new wxBitmapButton(this, 1024, bitmap_2, wxPoint(1133,11), wxSize(40,40));

    //panel3

//    panel3 = new wxPanel(this,3,wxPoint(10,201),wxSize(1173,559));
//    panel3->SetBackgroundColour(wxColour(23,34,56));

    int rows = MM.getSize();
    movies = new wxFlexGridSizer(rows+2,2,10,10);
    window = new wxScrolledWindow(this,1111,wxPoint(10,201),wxSize(1173,559));
    setMoviesDisplay(MM.getFutureMovies().getRepository());
    help_sizer = new wxBoxSizer(wxVERTICAL);
    movies->Add(help_sizer);
    window->SetSizer(movies);
    window->SetScrollRate(20, 20);
    window->FitInside();
//    window->Show();

    //clearMoviesDisplay();
}

void AdminMoviesFrame::searchButton(wxCommandEvent &evt) {
    std::string s = search->GetValue().ToStdString();
    if(s.length()==0)s="0";
    for(auto &item:vec)
    {
        if(item->IsChecked())
        {
            clearMoviesDisplay();
            switch(item->GetId())
            {
                case 1005:
                {
                    int rows = MM.getSize();
                    movies = new wxFlexGridSizer(rows+2,2,10,10);
                    setMoviesDisplay(MM.getFutureMovies().getRepository());
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(movies);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1006:
                {
                    std::string title = s;
                    strip(title);
                    boost::algorithm::to_lower(title);
                    MoviePredicate p = [title](MoviePtr m)->bool
                    {
                        std::string tmp_title = m->getTitle();
                        boost::algorithm::to_lower(tmp_title);
                        return tmp_title.find(title) != std::string::npos;
                    };
                    std::vector<MoviePtr> tmp_storage = MM.findMovies(p);

                    movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setMoviesDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(movies);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1007:
                {
                    if(isNumber(s))
                    {
                        int id_tmp = std::stoi(s);
                        MoviePredicate p = [id_tmp](MoviePtr m)->bool
                        {
                            return m->getId()==id_tmp;
                        };
                        std::vector<MoviePtr> tmp_storage = MM.findMovies(p);
                        movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setMoviesDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(movies);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1008:
                {
                    try {
                        pt::ptime data = convertStringToDate(s);
                        MoviePredicate p = [data](MoviePtr m)->bool
                        {
                            pt::ptime m_data = m->getStart();
                            if(m_data> data- pt::hours(7*24) && m_data<data +pt::hours(7*24) )
                                return true;
                            return false;
                        };
                        std::vector<MoviePtr> tmp_storage = MM.findMovies(p);
                        movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setMoviesDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(movies);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    catch(std::exception &e)
                    {
                        wxMessageBox( wxString(e.what()), wxT("Data error"), wxICON_INFORMATION);
                    }
                    break;
                }
                case 1009:
                {
                    if(isNumber(s)) {
                        int age = std::stoi(s);
                        MoviePredicate p = [age](MoviePtr m)->bool
                        {
                            return m->getAgeRequired()>=age;
                        };
                        std::vector<MoviePtr> tmp_storage = MM.findMovies(p);
                        movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setMoviesDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(movies);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1010:
                {
                    if(isNumber(s)) {
                        int price = std::stoi(s);
                        MoviePredicate p = [price](MoviePtr m)->bool
                        {
                            return m->getPrice()<=price;
                        };
                        std::vector<MoviePtr> tmp_storage = MM.findMovies(p);
                        movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setMoviesDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(movies);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1011:
                {
                    if(isNumber(s)) {
                        int id = std::stoi(s);
                        MoviePredicate p = [id](MoviePtr m)->bool
                        {
                            return m->getScreeningRoom()->getId()==id;
                        };
                        std::vector<MoviePtr> tmp_storage = MM.findMovies(p);
                        movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setMoviesDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(movies);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1012:
                {
                    std::string type = s;
                    strip(type);
                    boost::algorithm::to_lower(type);
                    MoviePredicate p = [type](MoviePtr m)->bool
                    {
                        std::string type_tmp = m->getType();
                        boost::algorithm::to_lower(type_tmp);
                        return type_tmp.find(type) != std::string::npos;
                    };
                    std::vector<MoviePtr> tmp_storage = MM.findMovies(p);

                    movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setMoviesDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(movies);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1013:
                {
                    if(isNumber(s)) {
                        int age = std::stoi(s);
                        MoviePredicate p = [age](MoviePtr m)->bool
                        {
                            return m->getAgeRequired()<=age;
                        };
                        std::vector<MoviePtr> tmp_storage = MM.findMovies(p);
                        movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setMoviesDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(movies);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1014:
                {
                    if(isNumber(s)) {
                        int min = std::stoi(s);
                        MoviePredicate p = [min](MoviePtr m)->bool
                        {
                            return m->getScreeningRoom()->getBoughtPlaces(m)>=min;
                        };
                        std::vector<MoviePtr> tmp_storage = MM.findMovies(p);
                        movies = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setMoviesDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(movies);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
            }
        }
    }
}

void AdminMoviesFrame::checkBoxes(wxCommandEvent &evt) {
    int id = evt.GetId();
    for(auto &item:vec)
    {
        if(item->GetId()!=id)item->SetValue(false);
    }
}

void AdminMoviesFrame::addNew(wxCommandEvent &evt) {
    newMovie = new AdminAddMovie(this,1050);
    newMovie->Show(true);
}

void AdminMoviesFrame::updateBarStatus(std::string info) {
    panel2_opis->SetLabel(wxString(info));
}

void AdminMoviesFrame::goToPrevious(wxCommandEvent &evt) {
    this->GetParent()->Show(true);
    this->GetParent()->SetPosition(this->GetPosition());
    this->Close();
}

AdminMoviesFrame::~AdminMoviesFrame() {
}

void AdminMoviesFrame::setMoviesDisplay(std::vector<MoviePtr> objects) {
    int amount = objects.size();
    int initial_x = 10;
    int initial_y = 200;
    int h_dif = 50;
    int size_x =1100;
    int size_y = 50;
    int initial_button_x = 1100;
    srand (time(NULL));
    wxBitmap bitmap_3(wxT("../../Images/arrow.xpm"));
    for(int i=0;i<amount;i++)
    {
        wxBitmapButton* but = new wxBitmapButton(window,1600+i,bitmap_3,/*wxPoint(initial_button_x,initial_y+i*h_dif+5)*/wxPoint(0,initial_y+i*h_dif+5),wxSize(40,40),0,wxDefaultValidator,std::to_string(i));
        wxStaticText* text = new wxStaticText(window,1700+objects[i]->getId(),objects[i]->getMovieInfo(),wxPoint(initial_x,initial_y+i*h_dif),wxSize(size_x,size_y),0,std::to_string(objects[i]->getId()));

        text->SetBackgroundColour(wxColour(rand()%128+128,rand()%128+128,rand()%128+128));
        but->Bind(wxEVT_BUTTON, &AdminMoviesFrame::resize, this);
        buttons_container.push_back(but);
        text_container.push_back(text);

        movies->Add(text);
        movies->Add(but);
    }
        movies->Add(new wxPanel(window,1800,wxPoint(initial_x,initial_y),wxSize(size_x,5*size_y)));
}

void AdminMoviesFrame::clearMoviesDisplay() {
    window->DestroyChildren();
    text_container.clear();
    buttons_container.clear();
}

void AdminMoviesFrame::resize(wxCommandEvent &evt) {
    if(!id)id=evt.GetId();
    if(evt.GetId()==id) {
        int index = std::stoi(static_cast<wxBitmapButton*>(evt.GetEventObject())->GetName().ToStdString());
        int old_x = 1100;
        int default_size_y = 50;
        int old_size_y = text_container[index]->GetSize().y;
        int new_size_y = 306;
        int delta;
        current_movie_id=std::stoi(text_container[index]->GetName().ToStdString());
        if (new_size_y - old_size_y)
        {
            delta = new_size_y - old_size_y;
        } else
        {
            delta = default_size_y - old_size_y;
            new_size_y = default_size_y;
        }
        int size = text_container.size();
        if (index + 1 != size)
        {
            for (int i = index + 1; i < size; i++) {
                wxPoint p1 = text_container[i]->GetPosition();
                p1.y += delta;
                text_container[i]->SetPosition(p1);
                wxPoint p2 = buttons_container[i]->GetPosition();
                p2.y += delta;
                buttons_container[i]->SetPosition(p2);
            }
        }
        text_container[index]->SetSize(wxSize(old_x, new_size_y));
        if(delta>0)
        {
            wxPoint tmp = text_container[index]->GetPosition();
            tmp.y+=default_size_y-5;
            int index_2 =MM.getMovie(current_movie_id)->getScreeningRoom()->getIndexById(current_movie_id);
            arPtr copy = MM.getMovie(current_movie_id)->getScreeningRoom()->getT()[index_2];
            seats = new wxGridSizer(16,32,0,0);
            holder = new wxScrolledWindow(window,1234,tmp,wxSize(900,256));
            int counter = 0;
            for(int i=0;i<16;i++)
            {
                for(int j=0;j<32;j++)
                {
                    wxButton* seat = new wxButton(holder,wxID_ANY,"-",wxDefaultPosition,wxSize(10,10));
                    if(copy->t[i][j])
                    {
                    seat->SetBackgroundColour(wxColour(0,200,0));
                    counter+=1;
                    }
                    else seat->SetBackgroundColour(wxColour(200,0,0));
                    seats->Add(seat,0,wxALL|wxEXPAND);
                }
            }
            wxBitmap bitmap_4(wxT("../../Images/delete.xpm"));
            tmp.x+=900;
            free_seats=counter;
            description = new wxStaticText(window,1246,"Ilosc wolnych miejsc: "+std::to_string(free_seats),tmp,wxDefaultSize);
            tmp.y+=215;
            tmp.x+=150;
            delete_movie = new wxBitmapButton(window,1245,bitmap_4,tmp,wxSize(40,40));
            holder->SetSizer(seats);
            holder->FitInside();
        }
        else
        {
            delete description;
            delete delete_movie;
            holder->DestroyChildren();
            id=0;
        }
    }
}

void AdminMoviesFrame::deleteMovie(wxCommandEvent &evt) {
    if(free_seats!=512) wxMessageBox( wxString("Nie mozna usunac filmu, poniewaz ktos juz kupil bilet!"), wxT("Usun film"), wxICON_INFORMATION);
    else{
        AdminConfirmDeleteMovie* win = new AdminConfirmDeleteMovie(this,wxID_ANY);
        win->Show();
    }
}

const int AdminMoviesFrame::getCurrentMovieId() {
    return current_movie_id;
}

void AdminMoviesFrame::refresh() {
    clearMoviesDisplay();
    int rows = MM.getSize();
    movies = new wxFlexGridSizer(rows+2,2,10,10);
    setMoviesDisplay(MM.getFutureMovies().getRepository());
    window->SetSizer(movies);
    window->SetScrollRate(20, 20);
    window->FitInside();
}
