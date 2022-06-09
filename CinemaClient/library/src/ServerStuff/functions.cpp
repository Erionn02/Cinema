#include "ServerStuff/functions.h"
#include "typedefs.h"
#include "model/Client.h"
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include "Exceptions/ClientException.h"
#include "repositories/MovieRepository.h"
#include "repositories/ScreeningRoomRepository.h"
#include "Exceptions/MovieException.h"
#include <sstream>
#include <iostream>
#include "managers/MovieManager.h"
#include "managers/ClientManager.h"
#include "managers/ScreeningRoomManager.h"

//socket libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
std::vector<std::string> split(char* t,int len,std::string delim)
{
    std::vector<std::string> vec;
    std::string msg="";
    for(int i=0;i<len-1;i++)
    {
        msg+=t[i];
    }
    while(true){
        int ind = msg.find(delim);
        std::string token = msg.substr(0, ind);
        //cout<<msg<<" TOKEN:"<<token<<endl;
        vec.push_back(token);
        msg.erase(0, ind + delim.length());
        if(ind==-1)break;
    }
    return vec;
}
std::vector<std::string> split(std::string str,std::string delim)
{
    int len = str.length()+1;
    char t[len];
    strcpy(t,str.c_str());
    return split(t,len,delim);
}
void strip(std::string& str)
{
    if (str.length() == 0) {
        return;
    }

    auto start_it = str.begin();
    auto end_it = str.rbegin();
    while (std::isspace(*start_it)) {
        ++start_it;
        if (start_it == str.end()) break;
    }
    while (std::isspace(*end_it)) {
        ++end_it;
        if (end_it == str.rend()) break;
    }
    int start_pos = start_it - str.begin();
    int end_pos = end_it.base() - str.begin();
    str = start_pos <= end_pos ? std::string(start_it, end_it.base()) : "";
}
std::string convertMovieToStr(MoviePtr movie) {
    if (movie) {
        int id = movie->getId();
        int time = movie->getTime();
        int ageRequired = movie->getAgeRequired();
        double price = movie->getPrice();
        int id_screeningRoom = movie->getScreeningRoom()->getId();
        pt::ptime date = movie->getStart();
        std::stringstream ss;
        ss << date;
        return std::to_string(id) + "|" + movie->getTitle() + "|" + ss.str() + "|" + std::to_string(time) + "|" +
               std::to_string(ageRequired)
               + "|" + movie->getType() + "|" + std::to_string(price) + "|" + std::to_string(id_screeningRoom);
    } else throw MovieException("nullptr was passed");
}

std::string convertClientToStr(ClientPtr client) {
    if(client) {
        std::string name = client->getName();
        std::string lastName = client->getLastName();
        std::stringstream ss;
        ss<<client->getBirthDate();
        std::string birthDay = ss.str();
        int id = client->getId();
        double balance = client->getBalance();
        std::vector<TicketPtr> vec = client->getTickets();
        std::string ticketInfo="";
        for(int i=0;i<vec.size();i++)
        {
            double price = vec[i]->getPrice();
            int row = vec[i]->getRow();
            int column = vec[i]->getColumn();
            int movieID = vec[i]->getMovie()->getId();
            ticketInfo+=std::to_string(price)+" "+std::to_string(row)+" "+std::to_string(column)+" "+std::to_string(movieID);
            if(i!=vec.size()-1)ticketInfo+="/";
        }
        return name+"|"+lastName+"|"+birthDay+"|"+std::to_string(id)+"|"+std::to_string(balance)+"|"+ticketInfo;
    }else throw ClientException("Given client is nullptr");
}

std::string convertScreeningRoomToStr(ScreeningRoomPtr screeningRoom) {
    std::string info="";
    int id = screeningRoom->getId();
    info+=std::to_string(id)+"|";
    std::string arraysInfo="";
    std::string moviesInfo="";
    for(int i=0;i<screeningRoom->getSize();i++)
    {
        int x=screeningRoom->getMovies()[i]->getId();
        moviesInfo+=std::to_string(x)+",";
        std::string fullTable="";
        std::string tmp="";
        for(int j=0;j<16;j++)
        {

            for(int k=0;k<32;k++)
            {
                if(!screeningRoom->getT()[i]->t[j][k]){
                    tmp+=std::to_string(j)+"-"+std::to_string(k)+".";
                }
            }
        }
        if(tmp.length()>0)tmp=tmp.substr(0,tmp.length()-1);
        arraysInfo+=tmp+"+";
    }
    if(arraysInfo.length()>0)arraysInfo = arraysInfo.substr(0, arraysInfo.length() - 1);
    if(moviesInfo.length()>0)moviesInfo=moviesInfo.substr(0,moviesInfo.length()-1);
    arraysInfo+="|";
    return info+arraysInfo+moviesInfo;
}

MoviePtr convertStringToMovie(std::string info,ScreeningRoomRepository &SRP) {
    std::vector<std::string> vec = split(info,"|");
    int SR_ID = std::stoi(vec[7]);
    ScreeningRoomPtr screeningRoom = SRP.getObject(SR_ID);
    int id = std::stoi(vec[0]);
    std::string birthday = vec[2];
    pt::ptime data(pt::not_a_date_time);
    std::stringstream ss(birthday);
    ss>>data;
    int time = std::stoi(vec[3]);
    int ageRequired = std::stoi(vec[4]);
    double price = std::stod(vec[6]);
    std::string title = vec[1];
    std::string type = vec[5];
    MoviePtr m = std::make_shared<Movie>(id,title,data,time,ageRequired,type,screeningRoom,price);
    return m;
}
SegmentType ConvertTo(std::string letter) {
    SegmentType val;
    if(letter.length()==0)
    {
        val=A;
        return val;
    }
    int l = std::stoi(letter);
    switch (l) {
        case 0:{
            val=A;
            break;}
        case 1:{
            val=B;
            break;}
        case 2:{
            val=C;
            break;}
        case 3:{
            val=D;
            break;}
        case 4:{
            val=E;
            break;}
        case 5:{
            val=F;
            break;}
        case 6:{
            val=G;
            break;}
        case 7:{
            val=H;
            break;}
        case 8:{
            val=I;
            break;}
        case 9:{
            val=J;
            break;}
        case 10:{
            val=K;
            break;}
        case 11:{
            val=L;
            break;}
        case 12:{
            val=M;
            break;}
        case 13:{
            val=N;
            break;}
        case 14:{
            val=O;
            break;}
        case 15:{
            val=P;
            break;}
        case 16:{
            val=Q;
            break;}
        case 17:{
            val=R;
            break;}
        case 18:{
            val=S;
            break;}
        case 19:{
            val=T;
            break;}
        case 20:{
            val=U;
            break;}
        case 21:{
            val=V;
            break;}
        case 22:{
            val=W;
            break;}
        case 23:{
            val=X;
            break;}
        case 24:{
            val=Y;
            break;}
    }
    return val;
}
ClientPtr convertStringToClient(std::string info,MovieRepository &MR) {
    ClientPtr client;
    std::vector<std::string> vec = split(info,"|");
    std::string name = vec[0];
    std::string lastName = vec[1];
    std::string birthday = vec[2];
    pt::ptime data(pt::not_a_date_time);
    std::stringstream ss(birthday);
    ss>>data;
    std::string id = vec[3];
    std::string balance = vec[4];
    client = std::make_shared<Client>(name,lastName,data,std::stoi(id),std::stod(balance));
    std::string tickets_info = vec[5];
    if(tickets_info.length()>0)
    {std::vector<std::string> tickets = split(tickets_info,"/");
    for(auto &ticket:tickets)
    {
        std::vector<std::string> infos = split(ticket," ");
        int id = std::stoi(infos[3]);
        MoviePtr m = MR.getObject(id);
        SegmentType row = ConvertTo(infos[1]);
        int column = std::stoi(infos[2]);
        TicketPtr new_ticket = std::make_shared<Ticket>(m,row,column);
        client->addTicket(new_ticket);
    }}
    return client;
}
std::vector<std::string> exchangeInfoWithServer(std::string func_name, std::string message) {
    std::string ipAddress = "PUT YOURS SERVER IP HERE";
    int port = 5050;
    const int HEADER = 35;
    //std::string DISCONNECT_MESSAGE = "!DISCONNECT";
    struct sockaddr_in server_addr;
    socklen_t size;
    int client;
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        throw std::logic_error("Could not create a socket");
    }
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port = htons(port);
    int status = inet_pton(AF_INET, ipAddress.c_str(), &server_addr.sin_addr);
    if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0)
        throw std::logic_error("Could not connect to the server");

    int len = message.length()+1;
    func_name+= std::to_string(len);
    int h_len = func_name.length();
    h_len=HEADER-h_len;
    std::string pad(h_len,' ');
    message=func_name+pad+message;
    char t[message.length()+1];
    strcpy(t,message.c_str());
    int sendResult = send(client, t, sizeof(t), 0);
    if(sendResult!=-1)
    {
        //recieving server_info which is in header (exit_msg + length of actual message)
        char buf[HEADER+1];
        int bytesRecieved= recv(client,buf,sizeof(buf)-1,0);
        if(bytesRecieved>0)
        {
            //reading actual server info
            int len = sizeof(buf);
            std::vector<std::string> vec = split(buf,len,"_");
            //exit_msg
            std::string func_info = vec[0];
            //number of bytes in actual message
            std::string number= vec[1];
            //needs to be stripped due to some spaces after actual number
            strip(number);
            int amount_of_bytes = std::stoi(number);
            char message[amount_of_bytes+1];

            int isIt = recv(client,message,sizeof(message),0);
            std::string delim = "&";
            std::vector<std::string> vec2= split(message,amount_of_bytes+1,delim);
            close(client);
            return vec2;
        } else throw std::logic_error("Could not send data to the server.");
    }else close(client);
}

bool retrieveRepositoriesState(MovieRepository &MR, ScreeningRoomRepository &SRR) {
    std::vector<std::string> tmp_ids_movies= exchangeInfoWithServer("getMoviesIDs_","");
    std::vector<std::string> ids_movies = split(tmp_ids_movies[0],",");
    std::vector<std::string> moviesVector;
    for(int i=0;i<ids_movies.size();i++)
    {
        std::vector<std::string> movieInfo = exchangeInfoWithServer("retrieveMovieByID_",ids_movies[i]);
        moviesVector.push_back(movieInfo[0]);
    }
    std::vector<std::string> roomsVector;
    std::vector<std::string> tmp_ids_rooms= exchangeInfoWithServer("getScreeningRoomsIDs_","");
    std::vector<std::string> ids_rooms = split(tmp_ids_rooms[0],",");
    for(int i=0;i<ids_rooms.size();i++)
    {
        std::vector<std::string> roomInfo = exchangeInfoWithServer("retrieveScreeningRoomByID_",ids_rooms[i]);
        roomsVector.push_back(roomInfo[0]);
    }
//    przy wiekszej ilosci obiektow z jakiegos powodu (?) ponizej zakomentowane wywolania serwerowe nie dzialaly poprawnie- dane były całkowicie przesyłane (kilka KB),
//    ale niecałkowicie odbierane
//    podejrzewam, że chodzi o zbyt duży przesył danych jednokrotnie, zatem teraz dane są odbierane jednostkowo-
//    każdy obiekt, przy takim modelu powinienem zmienić model przesyłania danych na ciągłe połączenie, ale wymagałoby to zbyt wielu zmian w strukturze
//    na ktore w czasie realizowania projektu nie mialem czasu
//    std::vector<std::string> roomsVector = exchangeInfoWithServer("retrieveScreeningRooms_","");
//    std::vector<std::string> moviesVector= exchangeInfoWithServer("retrieveMovies_","");
    for(int i=0;i<roomsVector.size();i++)
    {
        std::string roomInfo = roomsVector[i];
        std::vector<std::string> RoomVector = split(roomInfo,"|");
        int id = std::stoi(RoomVector[0]);
        ScreeningRoomPtr s = std::make_shared<ScreeningRoom>(id);
        SRR.add(s);
        std::vector<std::string> seats = split(RoomVector[1],"+");
        std::vector<std::string> moviesIDs = split(RoomVector[2],",");
        for(int j=0;j<moviesIDs.size();j++)
        {
            for(int k = 0;k<moviesVector.size();k++)
            {
                std::string movieInfo = moviesVector[k];
                std::vector<std::string> movie = split(movieInfo,"|");
                if(moviesIDs[j]==movie[0])
                {
                    //std::vector<std::string> seats_for_this_movie = split(seats[j],".");
                    MoviePtr m = convertStringToMovie(movieInfo,SRR);
                    s->addMovie(m);
                    MR.add(m);
                }
            }
        }
    }
    return true;
}
ScreeningRoomPtr convertStringToScreeningRoom(std::string info,MovieRepository &MR) {
    std::vector<std::string> vec = split(info,"|");
    int id = std::stoi(vec[0]);
    std::vector<std::string> seats = split(vec[1],"+");
    std::vector<std::string> movieIDs = split(vec[2],",");
    ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(id);
    for(int i=0;i<seats.size();i++)
    {
        std::vector<std::string> tmp = split(seats[i],".");
        for(auto &seat:tmp)
        {
            std::vector<std::string> numbers = split(seat,"-");
            screeningRoom->rentSeat(std::stoi(numbers[0]),std::stoi(numbers[1]),MR.getObject(std::stoi(movieIDs[i])));
        }
    }
    return screeningRoom;
}
int getID() {
    std::vector<std::string> vec = exchangeInfoWithServer("getID_","");
    return std::stoi(vec[0]);
}

pt::ptime convertStringToDate(std::string date) {
    std::vector<std::string> vec = split(date,"-");
    if(vec.size()>=3)
    return pt::ptime(gr::date(std::stoi(vec[0]), std::stoi(vec[1]), std::stoi(vec[2])));
    else throw std::logic_error("Invalid date");
}

void retrieveDataBases(ClientManager &CM, MovieManager &MM, ScreeningRoomManager &SRM) {
    MovieRepository futureMovies;
    ScreeningRoomRepository rooms;
    ClientRepository CR;

    retrieveRepositoriesState(futureMovies,rooms);
    retrieveActiveUsers(CR,futureMovies);

    MM.setFutureMovies(futureMovies);
    SRM.setScreeningRooms(rooms);
    CM.setActiveClients(CR);
}

void retrieveActiveUsers(ClientRepository &CR,MovieRepository &MR) {
//    std::vector<std::string> vec = exchangeInfoWithServer("retrieveActiveUsers_","");
//    for(int i=0;i<vec.size();i++)
//    {
//        ClientPtr c = convertStringToClient(vec[i],MR);
//        CR.add(c);
//    }
    std::vector<std::string> tmp_ids = exchangeInfoWithServer("getUsersIDs_","");
    std::vector<std::string> ids = split(tmp_ids[0],",");
    for(int i=0;i<ids.size();i++)
    {
        std::vector<std::string> userInfo = exchangeInfoWithServer("retrieveUserByID_",ids[i]);
        ClientPtr c = convertStringToClient(userInfo[0],MR);
        CR.add(c);
    }
}

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

SegmentType convertNumToSegment(int num) {
    SegmentType val;
    switch (num){
        case 0: {
            val = A;
            break;
            }
        case 1: {
            val = B;
            break;
        }
        case 2: {
            val = C;
            break;
        }
        case 3: {
            val = D;
            break;
        }
        case 4: {
            val = E;
            break;
        }
        case 5: {
            val = F;
            break;
        }
        case 6: {
            val = G;
            break;
        }
        case 7: {
            val = H;
            break;
        }
        case 8: {
            val = I;
            break;
        }
        case 9: {
            val = J;
            break;
        }
        case 10: {
            val = K;
            break;
        }
        case 11: {
            val = L;
            break;
        }
        case 12: {
            val = M;
            break;
        }
        case 13: {
            val = N;
            break;
        }
        case 14: {
            val = O;
            break;
        }
        case 15: {
            val = P;
            break;
        }
        case 16: {
            val = Q;
            break;
        }
        case 17: {
            val = R;
            break;
        }
        case 18: {
            val = S;
            break;
        }
        case 19: {
            val = T;
            break;
        }
        case 20: {
            val = U;
            break;
        }
        case 21: {
            val = V;
            break;
        }
        case 22: {
            val = W;
            break;
        }
        case 23: {
            val = X;
            break;
        }
        case 24: {
            val = Y;
            break;
        }
    }
        return val;
}

