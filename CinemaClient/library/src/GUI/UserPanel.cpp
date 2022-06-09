#include "GUI/UserPanel.h"
#include "ServerStuff/functions.h"
#include <wx/scrolwin.h>
#include "model/Movie.h"
#include "model/ScreeningRoom.h"
#include <boost/algorithm/string.hpp>
#include "GUI/BuyTicketFrame.h"
#include "model/Client.h"
#include "model/Ticket.h"
#include "GUI/UserAddMoney.h"
#include "GUI/UserUnregister.h"

wxBEGIN_EVENT_TABLE(UserPanel,wxFrame)
                EVT_BUTTON(1001, UserPanel::searchButtonMovies)

                EVT_CHECKBOX(1005,UserPanel::checkBoxesMovies)
                EVT_CHECKBOX(1006,UserPanel::checkBoxesMovies)
                EVT_CHECKBOX(1007,UserPanel::checkBoxesMovies)
                EVT_CHECKBOX(1008,UserPanel::checkBoxesMovies)
                EVT_CHECKBOX(1009,UserPanel::checkBoxesMovies)
                EVT_CHECKBOX(1010,UserPanel::checkBoxesMovies)
                EVT_CHECKBOX(1011,UserPanel::checkBoxesMovies)
                EVT_CHECKBOX(1012,UserPanel::checkBoxesMovies)

                EVT_CHECKBOX(990,UserPanel::checkBoxesTickets)
                EVT_CHECKBOX(991,UserPanel::checkBoxesTickets)
                EVT_CHECKBOX(992,UserPanel::checkBoxesTickets)
                EVT_CHECKBOX(993,UserPanel::checkBoxesTickets)
                EVT_BUTTON(998, UserPanel::searchButtonTickets)

                EVT_BUTTON(1024,UserPanel::goToPrevious)
                EVT_BUTTON(1025,UserPanel::addMoneyToBalance)
                EVT_BUTTON(1026,UserPanel::unregister)

                EVT_BUTTON(1245,UserPanel::buyTicket)
wxEND_EVENT_TABLE()

UserPanel::UserPanel(wxFrame *parent, wxPoint point,ClientPtr thisClient):MyFrame(parent,1200,"Panel uzytkownika",point,wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX),thisClient(thisClient) {
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
    wxCheckBox* box7 = new wxCheckBox(panel1,1011,wxString("Typ filmu"),wxPoint(30,170));
    wxCheckBox* box8 = new wxCheckBox(panel1,1012,wxString("Maksymalny wymagany wiek"),wxPoint(130,170));
    vec.push_back(box1);
    vec.push_back(box2);
    vec.push_back(box3);
    vec.push_back(box4);
    vec.push_back(box5);
    vec.push_back(box6);
    vec.push_back(box7);
    vec.push_back(box8);
    box1->SetValue(true);


    //panel2

    panel2 = new wxPanel(this,205,wxPoint(910,1),wxSize(190,200));
    int num = MM.getSize();
    wxStaticBox* panel2_box = new wxStaticBox(this,1020,"",wxPoint(910,1),wxSize(275,100));

    wxBitmap bitmap_2(wxT("../../Images/Undo-icon1.xpm"));
    goBack = new wxBitmapButton(this, 1024, bitmap_2, wxPoint(1093,11), wxSize(40,40));
    wxBitmap bitmap_3(wxT("../../Images/dolar.xpm"));
    moneyButton = new wxBitmapButton(this, 1025, bitmap_3, wxPoint(1143,11), wxSize(40,40));
    wxBitmap bitmap_4(wxT("../../Images/delete.xpm"));
    unregisterButton = new wxBitmapButton(this, 1026, bitmap_4, wxPoint(1043,11), wxSize(40,40));
    briefUserInfo = new wxStaticText(this,wxID_ANY,"Imie: "+thisClient->getName()+"\n"+"Nazwisko: "+thisClient->getLastName()+"\n"+"Stan konta: "+std::to_string(thisClient->getBalance()),wxPoint(915,40));



    //panel3
    description2 = new wxStaticText(this,996,"Wyszukaj bilety po zadanym kryterium",wxPoint(915,102));
    panel3box = new wxStaticBox(this,997,"",wxPoint(910,90),wxSize(275,110));
    searchTickets = new wxTextCtrl(this,999,"",wxPoint(920,120),wxSize(160,40));
    search2 = new wxButton(this,998,"Szukaj",wxPoint(1080,120),wxSize(100,40));
    wxCheckBox* tbox1 = new wxCheckBox(this,990,wxString("Wszystkie"),wxPoint(910,160));
    wxCheckBox* tbox2 = new wxCheckBox(this,991,wxString("Po tytule"),wxPoint(1000,160));
    wxCheckBox* tbox3 = new wxCheckBox(this,992,wxString("W tym dniu (+-24h)"),wxPoint(910,178));
    wxCheckBox* tbox4 = new wxCheckBox(this,993,wxString("Sala"),wxPoint(1085,160));
    vec2.push_back(tbox1);
    vec2.push_back(tbox2);
    vec2.push_back(tbox3);
    vec2.push_back(tbox4);
    tbox1->SetValue(true);

    int rows = MM.getSize();
    movies = new wxFlexGridSizer(rows+2,2,10,10);
    window = new wxScrolledWindow(this,1111,wxPoint(10,201),wxSize(900,559));
    setMoviesDisplay(MM.getFutureMovies().getRepository());
    help_sizer = new wxBoxSizer(wxVERTICAL);
    movies->Add(help_sizer);
    window->SetSizer(movies);
    window->SetScrollRate(20, 20);
    window->FitInside();

    int rows_tickets = thisClient->getTickets().size();
    tickets= new wxFlexGridSizer(rows_tickets+1,1,5,5);
    ticketsWindow = new wxScrolledWindow(this,wxID_ANY,wxPoint(915,201),wxSize(280,559));
    setTicketsDisplay(thisClient->getTickets());
    ticketsWindow->SetSizer(tickets);
    ticketsWindow->SetScrollRate(20, 20);
    ticketsWindow->FitInside();
}

UserPanel::~UserPanel() {

}

const int UserPanel::getCurrentMovieId() {
    return current_movie_id;
}

void UserPanel::searchButtonTickets(wxCommandEvent &evt) {
    std::string s = searchTickets->GetValue().ToStdString();
    if(s.length()==0)s="0";
    for(auto &item:vec2)
    {
        if(item->IsChecked())
        {
            clearTicketsDisplay();
            switch(item->GetId())
            {
                case 990:
                {
                    tickets = new wxFlexGridSizer(thisClient->getTickets().size(),1,5,5);
                    setTicketsDisplay(thisClient->getTickets());
                    ticketsWindow->SetSizer(tickets);
                    ticketsWindow->SetScrollRate(20, 20);
                    ticketsWindow->FitInside();
                }
                case 991:
                {
                    std::string title = s;
                    strip(title);

                    boost::algorithm::to_lower(title);
                    std::vector<TicketPtr> tmp;
                    std::vector<TicketPtr> clientsTickets = thisClient->getTickets();
                    for(int i=0;i<clientsTickets.size();i++)
                    {
                        std::string tmp_title = clientsTickets[i]->getMovie()->getTitle();
                        boost::algorithm::to_lower(tmp_title);
                        if(tmp_title.find(title) != std::string::npos)
                            tmp.push_back(clientsTickets[i]);
                    }
                    tickets = new wxFlexGridSizer(tmp.size(),1,5,5);
                    setTicketsDisplay(tmp);
                    ticketsWindow->SetSizer(tickets);
                    ticketsWindow->SetScrollRate(20, 20);
                    ticketsWindow->FitInside();
                    break;
                }
                case 992:
                {
                    try {
                        pt::ptime data = convertStringToDate(s);
                        std::vector<TicketPtr> tmp;
                        std::vector<TicketPtr> clientsTickets = thisClient->getTickets();
                        for(int i=0;i<clientsTickets.size();i++)
                        {
                            pt::ptime m_data = clientsTickets[i]->getMovie()->getStart();
                            if(data+pt::hours(24)>m_data && data - pt::hours(24)<m_data)
                                tmp.push_back(clientsTickets[i]);
                        }
                        tickets = new wxFlexGridSizer(tmp.size(),1,5,5);
                        setTicketsDisplay(tmp);
                        ticketsWindow->SetSizer(tickets);
                        ticketsWindow->SetScrollRate(20, 20);
                        ticketsWindow->FitInside();
                        break;
                    }
                    catch(std::exception &e)
                    {
                        wxMessageBox( wxString(e.what()), wxT("Data error"), wxICON_INFORMATION);
                    }
                    break;
                }
                case 993:
                {
                    if(isNumber(s)) {
                        int roomId = std::stoi(s);
                        std::vector<TicketPtr> tmp;
                        std::vector<TicketPtr> clientsTickets = thisClient->getTickets();
                        for(int i=0;i<clientsTickets.size();i++)
                        {
                            if(clientsTickets[i]->getMovie()->getScreeningRoom()->getId()==roomId)
                                tmp.push_back(clientsTickets[i]);
                        }
                        tickets = new wxFlexGridSizer(tmp.size(),1,5,5);
                        setTicketsDisplay(tmp);
                        ticketsWindow->SetSizer(tickets);
                        ticketsWindow->SetScrollRate(20, 20);
                        ticketsWindow->FitInside();
                    }
                    break;
                }

                }
            }
        }
    }

void UserPanel::searchButtonMovies(wxCommandEvent &evt) {
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
                case 1012:
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
            }
        }
    }
}

void UserPanel::checkBoxesTickets(wxCommandEvent &evt) {
    int id = evt.GetId();
    for(auto &item:vec2)
    {
        if(item->GetId()!=id)item->SetValue(false);
    }
}

void UserPanel::checkBoxesMovies(wxCommandEvent &evt) {
    int id = evt.GetId();
    for(auto &item:vec)
    {
        if(item->GetId()!=id)item->SetValue(false);
    }
}
void UserPanel::goToPrevious(wxCommandEvent &evt) {
    this->GetParent()->Show(true);
    this->GetParent()->SetPosition(this->GetPosition());
    this->Close();
}

void UserPanel::refreshTickets() {
    clearTicketsDisplay();
    int rows2 = thisClient->getTickets().size();
    tickets= new wxFlexGridSizer(rows2,1,5,5);
    setTicketsDisplay(thisClient->getTickets());
    ticketsWindow->SetSizer(tickets);
    ticketsWindow->SetScrollRate(20, 20);
    ticketsWindow->FitInside();
}
void UserPanel::refreshMovies() {
    id=0;
    clearMoviesDisplay();
    int rows = MM.getSize();
    movies = new wxFlexGridSizer(rows+2,2,10,10);
    setMoviesDisplay(MM.getFutureMovies().getRepository());
    window->SetSizer(movies);
    window->SetScrollRate(20, 20);
    window->FitInside();
}
void UserPanel::setTicketsDisplay(std::vector<TicketPtr> objects) {
    int amount = objects.size();
    int h_dif = 50;
    int initial_x = 960;
    int initial_y = 220;
    int size_x=260;
    int size_y=60;
    for(int i=0;i<amount;i++)
    {
        wxStaticText* text = new wxStaticText(ticketsWindow,wxID_ANY,objects[i]->getTicketInfo(),wxPoint(initial_x,initial_y+i*h_dif),wxSize(size_x,size_y));
        text->SetBackgroundColour(wxColour(rand()%128+128,rand()%128+128,rand()%128+128));
        tickets->Add(text);
    }

}
void UserPanel::setMoviesDisplay(std::vector<MoviePtr> objects) {
    int amount = objects.size();
    int initial_x = 10;
    int initial_y = 200;
    int h_dif = 50;
    int size_x =830;
    int size_y = 50;
    int initial_button_x = 1100;
    srand (time(NULL));
    wxBitmap bitmap_3(wxT("../../Images/arrow.xpm"));
    for(int i=0;i<amount;i++)
    {
        wxBitmapButton* but = new wxBitmapButton(window,1600+i,bitmap_3,/*wxPoint(initial_button_x,initial_y+i*h_dif+5)*/wxPoint(0,initial_y+i*h_dif+5),wxSize(40,40),0,wxDefaultValidator,std::to_string(i));
        wxStaticText* text = new wxStaticText(window,1700+objects[i]->getId(),objects[i]->getMovieInfo(),wxPoint(initial_x,initial_y+i*h_dif),wxSize(size_x,size_y),0,std::to_string(objects[i]->getId()));

        text->SetBackgroundColour(wxColour(rand()%128+128,rand()%128+128,rand()%128+128));
        but->Bind(wxEVT_BUTTON, &UserPanel::resize, this);
        buttons_container.push_back(but);
        text_container.push_back(text);

        movies->Add(text);
        movies->Add(but);
    }
    movies->Add(new wxPanel(window,1800,wxPoint(initial_x,initial_y),wxSize(size_x,5*size_y)));
}

void UserPanel::clearMoviesDisplay() {
    window->DestroyChildren();
    previous_seat= nullptr;
    text_container.clear();
    buttons_container.clear();
}

void UserPanel::resize(wxCommandEvent &evt) {
    if(!id)id=evt.GetId();
    if(evt.GetId()==id) {
        int index = std::stoi(static_cast<wxBitmapButton*>(evt.GetEventObject())->GetName().ToStdString());
        int old_x = 830;
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
            holder = new wxScrolledWindow(window,1234,tmp,wxSize(700,256));
            int counter = 0;
            for(int i=0;i<16;i++)
            {
                for(int j=0;j<32;j++)
                {
                    wxButton* seat = new wxButton(holder,wxID_ANY,std::to_string(i)+"-"+std::to_string(j),wxDefaultPosition,wxSize(10,10));
                    seat->Bind(wxEVT_BUTTON, &UserPanel::updateSeat, this);
                    if(copy->t[i][j])
                    {
                        seat->SetBackgroundColour(wxColour(0,200,0));
                        counter+=1;
                    }
                    else seat->SetBackgroundColour(wxColour(200,0,0));
                    seats->Add(seat,0,wxALL|wxEXPAND);
                }
            }
            wxBitmap bitmap_4(wxT("../../Images/dolar.xpm"));
            tmp.x+=675;
            free_seats=counter;
            description = new wxStaticText(window,1246,std::to_string(free_seats)+" wolnych miejsc\n\nWybierz miejsce\nklikajac na zielony guzik\na potem zatwierdz\n\n\n\n\n\n\n\n\t\t\tKup",tmp,wxDefaultSize);
            tmp.y+=215;
            tmp.x+=110;
            buyButton = new wxBitmapButton(window,1245,bitmap_4,tmp,wxSize(40,40));
            holder->SetSizer(seats);
            holder->FitInside();
        }
        else
        {
            delete description;
            delete buyButton;
            holder->DestroyChildren();
            previous_seat=nullptr;
            id=0;
        }
    }
}

void UserPanel::deleteMovie(wxCommandEvent &evt) {

}

void UserPanel::updateBarStatus(std::string info) {
    panel2_opis->SetLabel(wxString(info));
}

void UserPanel::buyTicket(wxCommandEvent &evt) {
    BuyTicketFrame *buy = new BuyTicketFrame(this, wxID_ANY);
    buy->Show();
}

void UserPanel::updateSeat(wxCommandEvent &evt) {
    wxButton* tmp = static_cast<wxButton*>(evt.GetEventObject());
    if(tmp!=nullptr)
    {
        if(tmp->GetBackgroundColour()==wxColour(0,200,0))
        {
            tmp->SetBackgroundColour(wxColour(50,50,50));
            if(previous_seat!=nullptr)previous_seat->SetBackgroundColour(wxColour(0,200,0));
            previous_seat=tmp;
        }
        else if(tmp->GetBackgroundColour()==wxColour(50,50,50))
        {
            tmp->SetBackgroundColour(wxColour(0,200,0));
            previous_seat=nullptr;
        }
    }
}

const ClientPtr &UserPanel::getThisClient() const {
    return thisClient;
}

wxButton *UserPanel::getPreviousSeat() const {
    return previous_seat;
}

void UserPanel::clearTicketsDisplay() {
    ticketsWindow->DestroyChildren();
}

void UserPanel::unregister(wxCommandEvent &evt) {
    UserUnregister* tmpWindow = new UserUnregister(this);
    tmpWindow->Show(true);
}

void UserPanel::addMoneyToBalance(wxCommandEvent &evt) {
    UserAddMoney* tmpWindow = new UserAddMoney(this);
    tmpWindow->Show(true);
}

void UserPanel::updateClientInfo() {
    briefUserInfo->SetLabel("Imie: "+thisClient->getName()+"\n"+"Nazwisko: "+thisClient->getLastName()+"\n"+"Stan konta: "+std::to_string(thisClient->getBalance()));
}



