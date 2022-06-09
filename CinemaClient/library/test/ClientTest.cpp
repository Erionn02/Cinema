#include <boost/test/unit_test.hpp>
#include "model/Junior.h"
#include "model/Client.h"
#include "model/Senior.h"
#include "model/Concessionary.h"
#include "model/Regular.h"
#include "typedefs.h"
#include <memory>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include<boost/date_time.hpp>
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(ClientSuite)

    BOOST_AUTO_TEST_CASE(ClientInfoTests){
    pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
    pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
    pt::ptime data = pt::ptime (gr::date(2002,04,28));
    pt::ptime data1 = pt::ptime (gr::date(2020,04,28));
    pt::ptime data2 = pt::ptime (gr::date(2008,04,28));
    pt::ptime data3 = pt::ptime (gr::date(1940,04,28));
    ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
    ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
    MoviePtr movie = std::make_shared<Movie>(1,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom,15);
    MoviePtr movie1 = std::make_shared<Movie>(2,"StArY FiLm", startFilmu2, 120, 16, "Akcji", screeningRoom1,25);
    screeningRoom->addMovie(movie);
    screeningRoom1->addMovie(movie1);
    TicketPtr ticket = std::make_shared<Ticket>(movie, A, 10);
    TicketPtr ticket1 = std::make_shared<Ticket>(movie, A, 11);
    TicketPtr ticket2 = std::make_shared<Ticket>(movie1, D, 17);
    ClientPtr client = std::make_shared<Client>("Adam", "Nowak", data, 12345, 70.7);
    ClientPtr client1 = std::make_shared<Client>("Jan", "Kowalski", data1, 454545, 45.0);
    ClientPtr client2 = std::make_shared<Client>("Stanislaw", "Polak", data2, 99999, 50.1);
    ClientPtr client3 = std::make_shared<Client>("Grzegorz", "Wolny", data3, 55457, 390.0);
    client->addTicket(ticket);
    client->addTicket(ticket1);
    client1->addTicket(ticket2);
    client2->addTicket(ticket2);
    client3->addTicket(ticket2);

    BOOST_TEST_MESSAGE(client->getClientInfo());
    BOOST_TEST_MESSAGE(client1->getClientInfo());
    BOOST_TEST_MESSAGE(client2->getClientInfo());
    BOOST_TEST_MESSAGE(client3->getClientInfo());
    BOOST_TEST(client->getClientType()->getTypeInfo() == "Typ klienta: Normalny");
    BOOST_TEST(client1->getClientType()->getTypeInfo() == "Typ klienta: Junior");
    BOOST_TEST(client2->getClientType()->getTypeInfo() == "Typ klienta: Ulgowy");
    BOOST_TEST(client3->getClientType()->getTypeInfo() == "Typ klienta: Senior");
    }

    BOOST_AUTO_TEST_CASE(ClientGetterTests){
    pt::ptime data = pt::ptime (gr::date(2002,04,28));
    ClientPtr client = std::make_shared<Client>("Adam", "Nowak", data, 12345, 70.7);

    BOOST_TEST(client->getAge()==20);
    BOOST_TEST(client->getActive());
    BOOST_TEST(client->getName() == "Adam");
    BOOST_TEST(client->getLastName()=="Nowak");
    BOOST_TEST(client->getClientType()->getTypeInfo() == "Typ klienta: Normalny");
    BOOST_TEST(client->getId()==12345);
    BOOST_TEST(client->getBirthDate() == pt::ptime(gr::date(2002,04,28)));
    BOOST_REQUIRE_CLOSE(client->getBalance(), 70.7,0.001);
}
BOOST_AUTO_TEST_SUITE_END()