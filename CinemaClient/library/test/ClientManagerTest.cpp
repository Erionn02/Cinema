#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include <memory>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include "model/Client.h"
#include <boost/date_time.hpp>
#include "Exceptions/CinemaException.h"
#include "Exceptions/MovieException.h"
#include "managers/MovieManager.h"
#include "managers/ClientManager.h"
#include "Exceptions/ClientException.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(ClientManagerSuite)

    BOOST_AUTO_TEST_CASE(ClientManagerTests) {
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime data1 = pt::ptime (gr::date(2020,04,28));
        pt::ptime data2 = pt::ptime (gr::date(1963,04,28));
        ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
        MovieManager MM;
        int id=1;
        double price1 = 30;
        double price2 = 40;
        MoviePtr m1 = MM.addMovie(id,"Tytul", startFilmu2, 120, 16, "Akcji", screeningRoom1,price1);
        MoviePtr m2 = MM.addMovie(2,"NoWy FiLm", startFilmu, 120,  13, "Przygodowy", screeningRoom1,price2);
        ClientManager CR;
        double startBalance1=100;
        double startBalance2=130;
        std::string name1 = "Krzysztof";
        std::string name2 = "Andrzej";
        ClientPtr c1 = CR.registerClient(name1,"Kononowicz",data2,420,startBalance1);
        ClientPtr c2 = CR.registerClient(name2,"Krawczyk",data1,420,startBalance2);
        BOOST_REQUIRE_NO_THROW(CR.buyMovieTicket(c1,m1,A,10));
        BOOST_REQUIRE_CLOSE(c1->getBalance(),startBalance1-price1,0.01);
        BOOST_REQUIRE_NO_THROW(CR.buyMovieTicket(c1,m1,A,11));
        BOOST_REQUIRE_CLOSE(c1->getBalance(),startBalance1-2*price1,0.01);
        BOOST_REQUIRE_NO_THROW(CR.buyMovieTicket(c1,m2,A,11));
        BOOST_REQUIRE_CLOSE(c1->getBalance(),startBalance1-2*price1-price2,0.01);
        BOOST_TEST(CR.getSize()==2);
        BOOST_TEST_MESSAGE(CR.getClientsInfo());
        CR.unRegisterClient(c2);
        BOOST_TEST(CR.getSize()==1);
        BOOST_TEST(CR.getSize(false)==1);
        BOOST_TEST_MESSAGE(CR.getClientsInfo(false));
        ClientPredicate p1 = [name1](ClientPtr c)->bool{
            return c->getName()==name1;
        };
        BOOST_TEST(CR.findClients(p1).size()==1);
        ClientPredicate p2 = [](ClientPtr c)->bool{
            return c->getName()=="lodgneirg";
        };
        BOOST_TEST(CR.findClients(p2).size()==0);
        ClientPredicate p3 = [name2](ClientPtr c)->bool{
            return c->getName()==name2;
        };
        BOOST_TEST(CR.findClients(p3,false).size()==1);
    }
    BOOST_AUTO_TEST_CASE(ClientManagerExceptionsTest)
    {
        ClientManager CM;
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime data1 = pt::ptime (gr::date(2020,04,28));
        BOOST_REQUIRE_THROW(CM.registerClient("","Kononowicz",data1,420,0),ClientException);
        BOOST_REQUIRE_THROW(CM.registerClient("jakies imie","",data1,420,0),ClientException);
        BOOST_REQUIRE_THROW(CM.registerClient("jakies imie","Kononowicz",pt::not_a_date_time,420,0),ClientException);
        pt::ptime data2 = pt::ptime (gr::date(2050,04,28));
        BOOST_REQUIRE_THROW(CM.registerClient("jakies imie","Kononowicz",data2,420,0),ClientException);
        BOOST_REQUIRE_THROW(CM.unRegisterClient(nullptr),ClientException);
        BOOST_REQUIRE_THROW(CM.getClientInfo(nullptr),ClientException);
        BOOST_REQUIRE_THROW(CM.getClientTicketInfo(nullptr),ClientException);
        MovieManager MM;
        int id=1;
        pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom1=std::make_shared<ScreeningRoom>(5);
        double price1=30;
        MoviePtr m1 = MM.addMovie(id,"Tytul", startFilmu2, 120, 16, "Akcji", screeningRoom1,price1);
        ClientPtr c1 = CM.registerClient("Krzysztof","Kononowicz",data1,420,100);
        BOOST_REQUIRE_THROW(CM.buyMovieTicket(nullptr,m1,B,15),ClientException);
        BOOST_REQUIRE_THROW(CM.buyMovieTicket(c1,nullptr,B,15),MovieException);
        BOOST_REQUIRE_THROW(CM.buyMovieTicket(c1,m1,B,15),ClientException);
        pt::ptime data3 = pt::ptime (gr::date(2000,04,28));
        ClientPtr c2 = CM.registerClient("Krzysztof","Kononowicz",data3,420,100);
        CM.buyMovieTicket(c2,m1,B,15);
        CM.buyMovieTicket(c2,m1,B,16);
        CM.buyMovieTicket(c2,m1,B,17);
        BOOST_REQUIRE_THROW(CM.buyMovieTicket(c2,m1,B,18),ClientException);
        BOOST_TEST(c2->getBalance()==10);
    }
BOOST_AUTO_TEST_SUITE_END()