#include "GUI/AdminUsersFrame.h"
#include "ServerStuff/functions.h"
#include "model/Client.h"
#include "typedefs.h"
#include <boost/algorithm/string.hpp>
#include "GUI/AdminConfirmUnregisterUser.h"
#include "GUI/RegisterFrame.h"
#include "model/ClientType.h"

wxBEGIN_EVENT_TABLE(AdminUsersFrame,wxFrame)
                EVT_BUTTON(1001, AdminUsersFrame::searchButton)

                EVT_CHECKBOX(1005,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1006,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1007,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1008,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1009,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1010,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1011,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1012,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1013,AdminUsersFrame::checkBoxes)
                EVT_CHECKBOX(1014,AdminUsersFrame::checkBoxes)

                EVT_BUTTON(1022,AdminUsersFrame::addNew)
                EVT_BUTTON(1024,AdminUsersFrame::goToPrevious)

                EVT_BUTTON(1245,AdminUsersFrame::deleteUser)
wxEND_EVENT_TABLE()

AdminUsersFrame::AdminUsersFrame(wxFrame *parent, wxPoint point):MyFrame(parent,700,"Panel zarzadzania uzytkownikami",point,wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX) {
    panel1 = new wxPanel(this,1,wxPoint(10,1),wxSize(900,200));
    wxStaticBox* panel1_box = new wxStaticBox(this,1000,"",panel1->GetPosition(),panel1->GetSize());
    wxStaticText* panel1_opis = new wxStaticText(panel1,1003,"Wyszukaj uzytkownikow po zadanym kryterium:",wxPoint(30,30));
    search = new wxTextCtrl(panel1,1002,"",wxPoint(30,60),wxSize(600,50));
    panel1_button = new wxButton(panel1,1001,"Szukaj",wxPoint(630,60),wxSize(200,50));

    wxCheckBox* box1 = new wxCheckBox(panel1,1005,wxString("Wszystkie"),wxPoint(30,140));
    wxCheckBox* box2 = new wxCheckBox(panel1,1006,wxString("ID"),wxPoint(165,140));
    wxCheckBox* box3 = new wxCheckBox(panel1,1007,wxString("Imie"),wxPoint(240,140));
    wxCheckBox* box4 = new wxCheckBox(panel1,1008,wxString("Nazwisko"),wxPoint(310,140));
    wxCheckBox* box5 = new wxCheckBox(panel1,1009,wxString("Wiek conajmniej"),wxPoint(430,140));
    wxCheckBox* box6 = new wxCheckBox(panel1,1010,wxString("Mnimialnie posiadanych biletow"),wxPoint(580,140));
    wxCheckBox* box7 = new wxCheckBox(panel1,1011,wxString("Junior"),wxPoint(30,170));
    wxCheckBox* box8 = new wxCheckBox(panel1,1012,wxString("Ulgowy"),wxPoint(130,170));
    wxCheckBox* box9 = new wxCheckBox(panel1,1013,wxString("Normalny"),wxPoint(230,170));
    wxCheckBox* box10 = new wxCheckBox(panel1,1014,wxString("Senior"),wxPoint(330,170));
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
    int num = CM.getSize();
    panel2_opis = new wxStaticText(this,1021,"Ilosc uzytkownikow: "+std::to_string(num),wxPoint(920,30));
    wxStaticBox* panel2_box = new wxStaticBox(this,1020,"",wxPoint(910,1),wxSize(275,200));
    add_new = new wxButton(this,1022,"Dodaj nowy",wxPoint(920,50),wxSize(255,140));
    wxBitmap bitmap_2(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *goBack = new wxBitmapButton(this, 1024, bitmap_2, wxPoint(1133,11), wxSize(40,40));

    //panel3

//    panel3 = new wxPanel(this,3,wxPoint(10,201),wxSize(1173,559));
//    panel3->SetBackgroundColour(wxColour(23,34,56));

    int rows = CM.getSize();
    users = new wxFlexGridSizer(rows+2,2,10,10);
    window = new wxScrolledWindow(this,1111,wxPoint(10,201),wxSize(1173,559));
    setUsersDisplay(CM.getActiveClients().getRepository());
    help_sizer = new wxBoxSizer(wxVERTICAL);
    users->Add(help_sizer);
    window->SetSizer(users);
    window->SetScrollRate(20, 20);
    window->FitInside();
}

AdminUsersFrame::~AdminUsersFrame() {

}
void AdminUsersFrame::searchButton(wxCommandEvent &evt) {
    std::string s = search->GetValue().ToStdString();
    if(s.length()==0)s="0";
    for(auto &item:vec)
    {
        if(item->IsChecked())
        {
            clearUsersDisplay();
            switch(item->GetId())
            {
                case 1005:
                {
                    int rows = CM.getSize();
                    users = new wxFlexGridSizer(rows+2,2,10,10);
                    setUsersDisplay(CM.getActiveClients().getRepository());
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(users);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1006:
                {
                    if(isNumber(s))
                    {
                        int id_tmp = std::stoi(s);
                        ClientPredicate p = [id_tmp](ClientPtr c)->bool
                        {
                            return c->getId()==id_tmp;
                        };
                        std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                        users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setUsersDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(users);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1007:
                {
                    strip(s);
                    boost::algorithm::to_lower(s);
                    ClientPredicate p = [s](ClientPtr c)->bool
                    {
                        std::string tmp_name = c->getName();
                        boost::algorithm::to_lower(tmp_name);
                        return tmp_name.find(s) != std::string::npos;
                    };
                    std::vector<ClientPtr> tmp_storage = CM.findClients(p);

                    users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setUsersDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(users);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1008:
                {
                    strip(s);
                    boost::algorithm::to_lower(s);
                    ClientPredicate p = [s](ClientPtr c)->bool
                    {
                        std::string tmp_Lastname = c->getLastName();
                        boost::algorithm::to_lower(tmp_Lastname);
                        return tmp_Lastname.find(s) != std::string::npos;
                    };
                    std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                    users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setUsersDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(users);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1009:
                {
                    if(isNumber(s)) {
                        int age = std::stoi(s);
                        ClientPredicate p = [age](ClientPtr c)->bool
                        {
                            return c->getAge()>=age;
                        };
                        std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                        users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setUsersDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(users);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1010:
                {
                    if(isNumber(s)) {
                        int amount = std::stoi(s);
                        ClientPredicate p = [amount](ClientPtr c)->bool
                        {
                            return c->getTickets().size()>=amount;
                        };
                        std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                        users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setUsersDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(users);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1011:
                {
                    ClientPredicate p = [](ClientPtr foo)->bool
                    {
                        return foo->getClientType()->getTypeInfo()=="Typ klienta: Junior";
                    };
                    std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                    users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setUsersDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(users);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1012:
                {
                    ClientPredicate p = [](ClientPtr foo)->bool
                    {
                        return foo->getClientType()->getTypeInfo()=="Typ klienta: Ulgowy";
                    };
                    std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                    users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setUsersDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(users);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1013:
                {
                    ClientPredicate p = [](ClientPtr foo)->bool
                    {
                        return foo->getClientType()->getTypeInfo()=="Typ klienta: Normalny";
                    };
                    std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                    users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setUsersDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(users);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1014:
                {
                    ClientPredicate p = [](ClientPtr foo)->bool
                    {
                        return foo->getClientType()->getTypeInfo()=="Typ klienta: Senior";
                    };
                    std::vector<ClientPtr> tmp_storage = CM.findClients(p);
                    users = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setUsersDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(users);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
            }
        }
    }
}
void AdminUsersFrame::checkBoxes(wxCommandEvent &evt) {
    int id = evt.GetId();
    for(auto &item:vec)
    {
        if(item->GetId()!=id)item->SetValue(false);
    }
}
void AdminUsersFrame::updateBarStatus(std::string info) {
    panel2_opis->SetLabel(wxString(info));
}
void AdminUsersFrame::goToPrevious(wxCommandEvent &evt) {
    this->GetParent()->Show(true);
    this->GetParent()->SetPosition(this->GetPosition());
    this->Close();
}
void AdminUsersFrame::setUsersDisplay(std::vector<ClientPtr> objects) {
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
        //wxStaticText* text = new wxStaticText(window,1700+objects[i]->getId(),objects[i]->getClientInfo(),wxPoint(initial_x,initial_y+i*h_dif),wxSize(size_x,size_y));
        wxStaticText* text = new wxStaticText(window,1700+objects[i]->getId(),objects[i]->getInfo(),wxPoint(initial_x,initial_y+i*h_dif),wxSize(size_x,size_y),0,std::to_string(objects[i]->getId()));
        text->SetBackgroundColour(wxColour(rand()%128+128,rand()%128+128,rand()%128+128));
        but->Bind(wxEVT_BUTTON, &AdminUsersFrame::resize, this);
        buttons_container.push_back(but);
        text_container.push_back(text);
        users->Add(text);
        users->Add(but);
    }
    users->Add(new wxPanel(window,1800,wxPoint(initial_x,initial_y),wxSize(size_x,5*size_y)));
}

void AdminUsersFrame::clearUsersDisplay() {
    window->DestroyChildren();
    text_container.clear();
    buttons_container.clear();
}
void AdminUsersFrame::resize(wxCommandEvent &evt) {
    if(!id)id=evt.GetId();
    if(evt.GetId()==id) {
        int index = std::stoi(static_cast<wxBitmapButton*>(evt.GetEventObject())->GetName().ToStdString());
        int old_x = 1100;
        int default_size_y = 50;
        int old_size_y = text_container[index]->GetSize().y;
        int new_size_y = 130;
        int delta;
        current_user_id=std::stoi(text_container[index]->GetName().ToStdString());
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
//            int index_2 =MM.getMovie(current_user_id)->getScreeningRoom()->getIndexById(current_movie_id);
//            arPtr copy = MM.getMovie(current_user_id)->getScreeningRoom()->getT()[index_2];
            //seats = new wxGridSizer(16,32,0,0);
            holder = new wxScrolledWindow(window,1234,tmp,wxSize(900,256));

            wxBitmap bitmap_4(wxT("../../Images/delete.xpm"));
            std::vector<std::string> userData = exchangeInfoWithServer("getUsersVulnerableData_",std::to_string(current_user_id));
            userData=split(userData[0],"|");
            std::string info = "Login uzytkownika: "+userData[0]+"\nHaslo uzytkownika: "+userData[1]+"\nEmail uzytkownika: "+userData[2];
            //exchangeInfoWithServer("dummyCall_",info);
            //info = "siemaneczko";
            description = new wxStaticText(window,1246,info,tmp);
            tmp.y+=45;
            tmp.x+=1050;
            unregisterUser = new wxBitmapButton(window,1245,bitmap_4,tmp,wxSize(40,40));
            //holder->SetSizer(seats);
            holder->FitInside();
        }
        else
        {
            delete description;
            delete unregisterUser;
            holder->DestroyChildren();
            id=0;
        }
    }
}

const int AdminUsersFrame::getCurrentUserId() {
    return current_user_id;
}
void AdminUsersFrame::refresh() {
    clearUsersDisplay();
    int rows = CM.getSize();
    users = new wxFlexGridSizer(rows+2,2,10,10);
    setUsersDisplay(CM.getActiveClients().getRepository());
    window->SetSizer(users);
    window->SetScrollRate(20, 20);
    window->FitInside();
}

void AdminUsersFrame::deleteUser(wxCommandEvent &evt) {
    AdminConfirmUnregisterUser* win = new AdminConfirmUnregisterUser(this,wxID_ANY);
    win->Show(true);
}

void AdminUsersFrame::addNew(wxCommandEvent &evt) {
    RegisterFrame* newUserFrame = new RegisterFrame(this,this->GetPosition());
    newUserFrame->Show(true);
    this->Show(false);
}
