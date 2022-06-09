#ifndef INTRODUCTIONPROJECT_CLIENT_H
#define INTRODUCTIONPROJECT_CLIENT_H
#include "typedefs.h"
#include <boost/date_time.hpp>
#include <string>
namespace pt = boost::posix_time;
class Client {
private:
    std::string name;
    std::string lastName;
    pt::ptime birthDate;
    int id;
    double balance;
    int age;
    std::vector<TicketPtr> tickets;
    ClientTypePtr clientType;
    bool active;
public:
    Client(const std::string &name, const std::string &lastName, const pt::ptime &birthDate, int id, double balance);

    double getBalance() const;

    const std::vector<TicketPtr> &getTickets() const;

    bool isActive() const;

    ~Client();

    int getAge() const;

    void updateAge();

    const ClientTypePtr &getClientType() const;

    void setClientType(const ClientTypePtr &clientType);

    bool getActive() const;

    void setActive(bool active);

    const std::string &getName() const;

    const std::string &getLastName() const;

    const pt::ptime &getBirthDate() const;

    std::string getClientInfo()const;

    std::string getInfo()const; //metoda getInfo stworzona aby ujednolicic nazwy metod w klasach logiki
                                // poniewaz repozytoria tych klas są tworzone za pomocą template
    std::string getTicketsInfo()const;

    void setBalance(double balance);

    double getRealPrice(double price)const;

    void addTicket(TicketPtr ticket);

    int getId() const;
};


#endif //INTRODUCTIONPROJECT_CLIENT_H
