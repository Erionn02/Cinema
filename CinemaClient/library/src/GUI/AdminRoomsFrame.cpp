
#include "GUI/AdminRoomsFrame.h"
#include "ServerStuff/functions.h"
#include "model/ScreeningRoom.h"
#include "GUI/AdminAddRoom.h"
#include "model/Movie.h"
#include "GUI/AdminConfirmDeleteRoom.h"

wxBEGIN_EVENT_TABLE(AdminRoomsFrame,wxFrame)
                EVT_BUTTON(1001, AdminRoomsFrame::searchButton)

                EVT_CHECKBOX(1005,AdminRoomsFrame::checkBoxes)
                EVT_CHECKBOX(1006,AdminRoomsFrame::checkBoxes)
                EVT_CHECKBOX(1007,AdminRoomsFrame::checkBoxes)
                EVT_CHECKBOX(1008,AdminRoomsFrame::checkBoxes)
//                EVT_CHECKBOX(1009,AdminMoviesFrame::checkBoxes)
//                EVT_CHECKBOX(1010,AdminMoviesFrame::checkBoxes)

                EVT_BUTTON(1022,AdminRoomsFrame::addNew)
                EVT_BUTTON(1024,AdminRoomsFrame::goToPrevious)

                EVT_BUTTON(1245,AdminRoomsFrame::deleteRoom)
wxEND_EVENT_TABLE()

AdminRoomsFrame::AdminRoomsFrame(wxFrame *parent, wxPoint point): MyFrame(parent,800,"Panel zarzadzania salami kinowymi",point,wxSize(1200,800),wxMINIMIZE_BOX | wxCLOSE_BOX) {
    panel1 = new wxPanel(this,1,wxPoint(10,1),wxSize(900,200));
    wxStaticBox* panel1_box = new wxStaticBox(this,1000,"",panel1->GetPosition(),panel1->GetSize());
    wxStaticText* panel1_opis = new wxStaticText(panel1,1003,"Wyszukaj sale kinowe po zadanym kryterium:",wxPoint(30,30));
    search = new wxTextCtrl(panel1,1002,"",wxPoint(30,60),wxSize(600,50));
    panel1_button = new wxButton(panel1,1001,"Szukaj",wxPoint(630,60),wxSize(200,50));

    wxCheckBox* box1 = new wxCheckBox(panel1,1005,wxString("Wszystkie"),wxPoint(30,140));
    wxCheckBox* box2 = new wxCheckBox(panel1,1006,wxString("ID"),wxPoint(165,140));
    wxCheckBox* box3 = new wxCheckBox(panel1,1007,wxString("Co najmniej filmow"),wxPoint(230,140));
    wxCheckBox* box4 = new wxCheckBox(panel1,1008,wxString("Sala, na ktorej bedzie puszczany film o tytule"),wxPoint(400,140));
    //wxCheckBox* box6 = new wxCheckBox(panel1,1010,wxString("Cena nie wiecej niz"),wxPoint(700,140));
    vec.push_back(box1);
    vec.push_back(box2);
    vec.push_back(box3);
    vec.push_back(box4);
//    vec.push_back(box5);
//    vec.push_back(box6);
    box1->SetValue(true);


    //panel2

    panel2 = new wxPanel(this,205,wxPoint(910,1),wxSize(190,200));
    int num = SRM.getSize();
    panel2_opis = new wxStaticText(this,1021,"Ilosc sal kinowych: "+std::to_string(num),wxPoint(920,30));
    wxStaticBox* panel2_box = new wxStaticBox(this,1020,"",wxPoint(910,1),wxSize(275,200));
    add_new = new wxButton(this,1022,"Dodaj nowy",wxPoint(920,50),wxSize(255,140));
    wxBitmap bitmap_2(wxT("../../Images/Undo-icon1.xpm"));
    wxBitmapButton *goBack = new wxBitmapButton(this, 1024, bitmap_2, wxPoint(1133,11), wxSize(40,40));

    int rows = SRM.getSize();
    rooms = new wxFlexGridSizer(rows+2,2,10,10);
    window = new wxScrolledWindow(this,1111,wxPoint(10,201),wxSize(1173,559));
    setRoomsDisplay(SRM.getScreeningRooms().getRepository());
    help_sizer = new wxBoxSizer(wxVERTICAL);
    rooms->Add(help_sizer);
    window->SetSizer(rooms);
    window->SetScrollRate(20, 20);
    window->FitInside();
}

AdminRoomsFrame::~AdminRoomsFrame() {

}

void AdminRoomsFrame::searchButton(wxCommandEvent &evt) {
    std::string s = search->GetValue().ToStdString();
    if(s.length()==0)s="0";
    for(auto &item:vec)
    {
        if(item->IsChecked())
        {
            clearRoomsDisplay();
            switch(item->GetId())
            {
                case 1005:
                {
                    int rows = SRM.getSize();
                    rooms = new wxFlexGridSizer(rows+2,2,10,10);
                    setRoomsDisplay(SRM.getScreeningRooms().getRepository());
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(rooms);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                    break;
                }
                case 1006:
                {
                    if(isNumber(s))
                    {
                        int id_tmp = std::stoi(s);
                        ScreeningRoomPredicate p = [id_tmp](ScreeningRoomPtr room)->bool
                        {
                            return room->getId()==id_tmp;
                        };
                        std::vector<ScreeningRoomPtr> tmp_storage = SRM.findRooms(p);
                        rooms = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setRoomsDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(rooms);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1007:
                {
                    if(isNumber(s))
                    {
                        int amount = std::stoi(s);
                        ScreeningRoomPredicate p = [amount](ScreeningRoomPtr room)->bool
                        {
                            return room->getSize()>=amount;
                        };
                        std::vector<ScreeningRoomPtr> tmp_storage = SRM.findRooms(p);
                        rooms = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                        setRoomsDisplay(tmp_storage);
                        //help_sizer = new wxBoxSizer(wxVERTICAL);
                        //movies->Add(help_sizer);
                        window->SetSizer(rooms);
                        window->SetScrollRate(20, 20);
                        window->FitInside();
                    }
                    break;
                }
                case 1008:
                {
                    strip(s);
                    boost::algorithm::to_lower(s);
                    ScreeningRoomPredicate p = [s](ScreeningRoomPtr room)->bool
                    {
                        bool flag = false;
                        for(auto &movie:room->getMovies())
                        {
                            std::string tmp_title = movie->getTitle();
                            boost::algorithm::to_lower(tmp_title);
                            if(tmp_title.find(s) != std::string::npos)
                            {
                                flag=true;
                                break;
                            }
                        }
                        return flag;
                    };
                    std::vector<ScreeningRoomPtr> tmp_storage = SRM.findRooms(p);
                    rooms = new wxFlexGridSizer(tmp_storage.size()+2,2,10,10);
                    setRoomsDisplay(tmp_storage);
                    //help_sizer = new wxBoxSizer(wxVERTICAL);
                    //movies->Add(help_sizer);
                    window->SetSizer(rooms);
                    window->SetScrollRate(20, 20);
                    window->FitInside();
                }
            }
        }
    }
}


void AdminRoomsFrame::checkBoxes(wxCommandEvent &evt) {
    int id = evt.GetId();
    for(auto &item:vec)
    {
        if(item->GetId()!=id)item->SetValue(false);
    }
}

void AdminRoomsFrame::addNew(wxCommandEvent &evt) {
    newRoom = new AdminAddRoom(this,1050);
    newRoom->Show(true);
}

void AdminRoomsFrame::goToPrevious(wxCommandEvent &evt) {
    this->GetParent()->Show(true);
    this->GetParent()->SetPosition(this->GetPosition());
    this->Close();
}

void AdminRoomsFrame::setRoomsDisplay(std::vector<ScreeningRoomPtr> objects) {
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
        wxStaticText* text = new wxStaticText(window,1700+objects[i]->getId(),objects[i]->getGeneralInfo(),wxPoint(initial_x,initial_y+i*h_dif),wxSize(size_x,size_y),0,std::to_string(objects[i]->getId()));

        text->SetBackgroundColour(wxColour(rand()%128+128,rand()%128+128,rand()%128+128));
        but->Bind(wxEVT_BUTTON, &AdminRoomsFrame::resize, this);
        buttons_container.push_back(but);
        text_container.push_back(text);

        rooms->Add(text);
        rooms->Add(but);
    }
    rooms->Add(new wxPanel(window,1800,wxPoint(initial_x,initial_y),wxSize(size_x,5*size_y)));
}

void AdminRoomsFrame::clearRoomsDisplay() {
    window->DestroyChildren();
    text_container.clear();
    buttons_container.clear();
}

void AdminRoomsFrame::resize(wxCommandEvent &evt) {
    try {
        if (!id)id = evt.GetId();
        if (evt.GetId() == id) {
            int index = std::stoi(static_cast<wxBitmapButton*>(evt.GetEventObject())->GetName().ToStdString());
            int old_x = 1100;
            int default_size_y = 50;
            int old_size_y = text_container[index]->GetSize().y;
            int new_size_y = 150;
            int delta;
            current_room_id = std::stoi(text_container[index]->GetName().ToStdString());
            if (new_size_y - old_size_y) {
                delta = new_size_y - old_size_y;
            } else {
                delta = default_size_y - old_size_y;
                new_size_y = default_size_y;
            }
            int size = text_container.size();
            if (index + 1 != size) {
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
            if (delta > 0) {
                wxPoint tmp = text_container[index]->GetPosition();
                tmp.y += default_size_y - 5;
                seats = new wxGridSizer(16, 32, 0, 0);
                holder = new wxScrolledWindow(window, 1234, tmp, wxSize(900, 256));
                wxBitmap bitmap_4(wxT("../../Images/delete.xpm"));
                description = new wxStaticText(window, 1246, "Najblizej grany film: \n"+
                                                             SRM.findById(current_room_id)->nearestPlayed(), tmp,
                                               wxSize(1000,200));
                tmp.y += 60;
                tmp.x += 1050;
                delete_movie = new wxBitmapButton(window, 1245, bitmap_4, tmp, wxSize(40, 40));
                holder->SetSizer(seats);
                holder->FitInside();
            } else {
                delete description;
                delete delete_movie;
                holder->DestroyChildren();
                id = 0;
            }
        }
    }
    catch(std::exception &e){
        wxMessageBox( wxString(e.what()), wxT("Error"), wxICON_INFORMATION);
    }
}

void AdminRoomsFrame::deleteRoom(wxCommandEvent &evt) {
    if(!SRM.findById(current_room_id)->getSize())
    {
        AdminConfirmDeleteRoom* tmp = new AdminConfirmDeleteRoom(this,wxID_ANY);
        tmp->Show(true);
    }else wxMessageBox( wxString("Nie mozna usunac sali kinowej, na ktorej jest zaplanowany film"), wxT("Error"), wxICON_INFORMATION);
}

void AdminRoomsFrame::updateBarStatus(std::string info) {
    panel2_opis->SetLabel(wxString(info));
}

void AdminRoomsFrame::refresh() {
    clearRoomsDisplay();
    int rows = SRM.getSize();
    rooms = new wxFlexGridSizer(rows+2,2,10,10);
    setRoomsDisplay(SRM.getScreeningRooms().getRepository());
    window->SetSizer(rooms);
    window->SetScrollRate(20, 20);
    window->FitInside();
}

const int AdminRoomsFrame::getCurrentRoomId() {
    return current_room_id;
}
