#include "model/Client.h"
#include <sstream>
#include "model/Ticket.h"
#include "model/ClientType.h"
#include "model/Junior.h"
#include "model/Senior.h"
#include "model/Concessionary.h"
#include "model/Regular.h"
#include "Exceptions/ClientException.h"

Client::Client(const std::string &name, const std::string &lastName, const pt::ptime &birthDate, int id, double balance)
        : name(name), lastName(lastName), birthDate(birthDate), id(id), balance(balance) , active(true){
    if(birthDate>pt::second_clock::local_time())throw ClientException("Invalid client's birth date");
    pt::time_period period(birthDate, pt::second_clock::local_time());
    age = period.length().hours() / (24 * 365);
    ClientTypePtr type;
    if(age<=4)  type = std::make_shared<Junior>();
    else if (age<=18)  type = std::make_shared<Concessionary>();
    else if (age<65)  type = std::make_shared<Regular>();
    else type = std::make_shared<Senior>();
    clientType = type;
}


int Client::getAge() const {
    return age;
}

void Client::updateAge() {
    pt::time_period period(birthDate, pt::second_clock::local_time());
    age = period.length().hours() / (24 * 365);
}

const ClientTypePtr &Client::getClientType() const {
    return clientType;
}

void Client::setClientType(const ClientTypePtr &clientType) {
    Client::clientType = clientType;
}

bool Client::getActive() const {
    return active;
}

void Client::setActive(bool flag) {
    if(!flag) active = flag; //zdezaktywowanego konta klienta nie da się znowu aktywować
}

const std::string &Client::getName() const {
    return name;
}

const std::string &Client::getLastName() const {
    return lastName;
}

const pt::ptime &Client::getBirthDate() const {
    return birthDate;
}

int Client::getId() const {
    return id;
}

Client::~Client() {

}

std::string Client::getClientInfo() const {
    std::stringstream ss;
    ss<<birthDate;
    int size=tickets.size();
    std::string act;
    if(active)act="tak";
    else act="nie";
    return "Klient "+name+" "+lastName+" wiek: "+std::to_string(age)+" data urodzenia: "+ss.str()+" stan konta: "+std::to_string(balance)+
    " "+clientType->getTypeInfo()+" Ilosc posiadanych biletow: "+std::to_string(size);
}

std::string Client::getTicketsInfo() const {
    std::string s="";
    for(int i=0;i<tickets.size();i++)
    {
        s+=tickets[i]->getTicketInfo();
        s+="\n";
    }
    return s;
}

void Client::addTicket(TicketPtr ticket) {
    tickets.push_back(ticket);
}

double Client::getBalance() const {
    return balance;
}

bool Client::isActive() const {
    return active;
}

std::string Client::getInfo() const {
    return getClientInfo();
}

double Client::getRealPrice(double price) const {
    return price-clientType->applyDiscount(price);
}

void Client::setBalance(double balance) {
    Client::balance = balance;
}

const std::vector<TicketPtr> &Client::getTickets() const {
    return tickets;
}
