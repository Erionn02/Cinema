//
// Created by student on 16.05.2022.
//

#ifndef INTRODUCTIONPROJECT_CLIENTMANAGER_H
#define INTRODUCTIONPROJECT_CLIENTMANAGER_H
#include "typedefs.h"
#include "repositories/ClientRepository.h"
#include <vector>
#include <boost/date_time.hpp>
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
class ClientManager {
ClientRepository activeClients;
ClientRepository inActiveClients;
public:
    virtual ~ClientManager();
    ClientPtr registerClient(const std::string &name, const std::string &lastName, const pt::ptime &birthDate, int id, double balance=0);
    void unRegisterClient(ClientPtr client);
    ClientPtr getClient(int id,bool flag=true)const;//flagi są po to, żeby nie powielać metod. Domyślnie flaga ustawiona na true
                                                //co oznacza że metoda realizuje dzialania dla pola activeClients, w przeciwnym wypadku dla inActiveClients
    std::vector<ClientPtr> findClients(ClientPredicate p,bool flag=true)const;
    int getSize(bool flag=true);
    std::string getClientInfo(ClientPtr client)const;
    std::string getClientTicketInfo(ClientPtr client)const;
    std::string getClientsInfo(bool flag=true)const;
    ClientRepository getActiveClients() const;

    void setActiveClients(const ClientRepository &activeClients);

    void setInActiveClients(const ClientRepository &inActiveClients);

    ClientRepository getInActiveClients() const;
    void buyMovieTicket(ClientPtr client,MoviePtr movie,SegmentType row, int column);
};


#endif //INTRODUCTIONPROJECT_CLIENTMANAGER_H
