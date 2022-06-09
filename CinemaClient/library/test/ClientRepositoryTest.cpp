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
#include <boost/date_time.hpp>
#include "repositories/ClientRepository.h"
#include "Exceptions/CinemaException.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(ClientRepositorySuite)

    BOOST_AUTO_TEST_CASE(ClientRepositoryTests){
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime data = pt::ptime (gr::date(2002,04,28));
        pt::ptime data1 = pt::ptime (gr::date(2020,04,28));
        pt::ptime data2 = pt::ptime (gr::date(2008,04,28));
        pt::ptime data3 = pt::ptime (gr::date(1940,04,28));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
        MoviePtr movie = std::make_shared<Movie>(1,"NoWy FiLm", startFilmu, 120,  13, "Przygodowy", screeningRoom,25);
        MoviePtr movie1 = std::make_shared<Movie>(2,"StArY FiLm", startFilmu2, 120, 16, "Akcji", screeningRoom1,15);
        screeningRoom->addMovie(movie);
        screeningRoom1->addMovie(movie1);
        TicketPtr ticket = std::make_shared<Ticket>(movie, A, 10);
        TicketPtr ticket1 = std::make_shared<Ticket>(movie, A, 11);
        TicketPtr ticket2 = std::make_shared<Ticket>(movie1, D, 17);
        std::string name="Adam";
        ClientPtr client = std::make_shared<Client>("Grzegorz", "Nowak", data, 12345, 70.7);
        ClientPtr client1 = std::make_shared<Client>("Jan", "Kowalski", data1, 454545, 45.0);
        ClientPtr client2 = std::make_shared<Client>("Stanislaw", "Polak", data2, 99999, 50.1);
        ClientPtr client3 = std::make_shared<Client>(name, "Wolny", data3, 55457, 390.0);
        client->addTicket(ticket);
        client->addTicket(ticket1);
        client1->addTicket(ticket2);
        client2->addTicket(ticket2);
        client3->addTicket(ticket2);

        ClientRepository CR;
        CR.add(client);
        CR.add(client1);
        CR.add(client2);
        CR.add(client3);

        BOOST_TEST(CR.getSize()==4);
        BOOST_TEST(CR.findAll().size()==4);
        BOOST_TEST(CR.getRepository().size()==CR.getSize());
        std::function<bool(std::shared_ptr<Client>)> f=[name](std::shared_ptr<Client> obj)->bool
        {
            return obj->getName()==name;
        };
        BOOST_TEST(CR.findBy(f).size()==1);
        BOOST_TEST(CR.findBy(f)[0]==client3);
        BOOST_TEST(CR.getObjectInfo(client3)==client3->getInfo());
        CR.remove(client3);
        BOOST_REQUIRE(CR.getSize()==3);
        BOOST_TEST(CR.getObject(12345)==client);
        BOOST_TEST(CR.getObjectByIndex(0)==client);
        BOOST_TEST_MESSAGE(CR.getObjectsInfo());
    }

    BOOST_AUTO_TEST_CASE(ClientRepositoryExceptionsTest){
        pt::ptime data = pt::ptime (gr::date(2002,04,28));
        ClientPtr client = std::make_shared<Client>("Adam", "Nowak", data, 12345, 70.7);
        ClientRepository CR;

        BOOST_REQUIRE_THROW(CR.add(nullptr),CinemaException);
        BOOST_REQUIRE_THROW(CR.remove(nullptr),CinemaException);
        BOOST_REQUIRE_THROW(CR.remove(client),CinemaException);
        BOOST_REQUIRE_THROW(CR.getObjectByIndex(0),CinemaException);
        BOOST_REQUIRE_THROW(CR.getObjectByIndex(-1),CinemaException);
        BOOST_REQUIRE_THROW(CR.getObjectInfo(nullptr),CinemaException);
        CR.add(client);
        BOOST_REQUIRE_THROW(CR.add(client),CinemaException);
    }
BOOST_AUTO_TEST_SUITE_END()

