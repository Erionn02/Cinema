#include "managers/ClientManager.h"
#include "model/Client.h"
#include "Exceptions/ClientException.h"
#include "model/Movie.h"
#include "Exceptions/MovieException.h"
#include "model/Ticket.h"
#include "model/ClientType.h"
ClientManager::~ClientManager() {

}

ClientRepository ClientManager::getActiveClients() const {
    return activeClients;
}
ClientRepository ClientManager::getInActiveClients() const {
    return inActiveClients;
}

ClientPtr ClientManager::registerClient(const std::string &name, const std::string &lastName, const pt::ptime &birthDate, int id,
                              double balance) {
    //dodac pozniej check id itp
    if(name=="")throw ClientException("Name must be specified");
    if(lastName=="")throw ClientException("Lastname must be specified");
    if(birthDate==pt::not_a_date_time)throw ClientException("Birthday must be specified");
    if(birthDate>pt::second_clock::local_time()) throw ClientException("Birthday can not be set as future date");
    ClientPtr c = std::make_shared<Client>(name,lastName,birthDate,id,balance);
    activeClients.add(c);
    return c;
}

void ClientManager::unRegisterClient(ClientPtr client) {
    if(client)
    {
        activeClients.remove(client);
        inActiveClients.add(client);
    }
    else throw ClientException("Given client does not exist");
}

ClientPtr ClientManager::getClient(int id, bool flag) const {
    if(flag)return activeClients.getObject(id);
    return inActiveClients.getObject(id);
}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate p, bool flag) const {
    if(flag)return activeClients.findBy(p);
    return inActiveClients.findBy(p);
}

std::string ClientManager::getClientInfo(ClientPtr client)const {
    if(client)
    return client->getClientInfo();
    throw ClientException("Given client is invalid");
}

std::string ClientManager::getClientTicketInfo(ClientPtr client)const {
    if(client)
    return client->getTicketsInfo();
    throw ClientException("Given client is invalid");
}

std::string ClientManager::getClientsInfo(bool flag) const {
    if(flag)return activeClients.getObjectsInfo();
    return inActiveClients.getObjectsInfo();
}

void ClientManager::buyMovieTicket(ClientPtr client, MoviePtr movie, SegmentType row, int column) {
    if(!client) throw ClientException("Given client does not exist");
    if(!movie)throw MovieException("Given movie does not exist");
    if(client->getAge()<movie->getAgeRequired())throw ClientException("Given client is too young to watch this movie ("+std::to_string(client->getAge())+"<"+std::to_string(movie->getAgeRequired())+")");
    double price = movie->getPrice();
    price=client->getRealPrice(price);
    double balance = client->getBalance();
    if(balance<price)throw ClientException("Client's balance is too low to buy ticket to the movie");
    TicketPtr ticket= std::make_shared<Ticket>(movie,row,column);
    balance-=price;
    client->setBalance(balance);
    client->addTicket(ticket);
}

int ClientManager::getSize(bool flag) {
    if(flag)return activeClients.getSize();
    return inActiveClients.getSize();
}

void ClientManager::setActiveClients(const ClientRepository &activeClients) {
    ClientManager::activeClients = activeClients;
}

void ClientManager::setInActiveClients(const ClientRepository &inActiveClients) {
    ClientManager::inActiveClients = inActiveClients;
}

