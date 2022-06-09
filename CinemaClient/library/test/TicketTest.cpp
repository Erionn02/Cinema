#include <boost/test/unit_test.hpp>
#include "model/Ticket.h"
#include "model/Movie.h"
#include "model/ScreeningRoom.h"
#include <memory>
#include "Exceptions/TicketException.h"
#include "Exceptions/CinemaException.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
BOOST_AUTO_TEST_SUITE(TicketRoomSuite)

    BOOST_AUTO_TEST_CASE(TicketGetterTests){
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu = pt::ptime (gr::date(2023, 05,14), pt::hours(19)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        MoviePtr movie = std::make_shared<Movie>(10,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom,10);
        screeningRoom->addMovie(movie);
        TicketPtr ticket = std::make_shared<Ticket>(movie, A, 11);
        BOOST_TEST(ticket->getPrice() == 10);
        BOOST_TEST(ticket->getRow() == A);
        BOOST_TEST(ticket->getColumn() == 11);
        BOOST_TEST(!screeningRoom->isSeatValid(A,11,movie));
        BOOST_TEST_MESSAGE(ticket->getTicketInfo());
}
    BOOST_AUTO_TEST_CASE(TicketExceptionsTests){
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu = pt::ptime (gr::date(2023, 05,14), pt::hours(19)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        MoviePtr movie = std::make_shared<Movie>(10,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom);
        screeningRoom->addMovie(movie);
        TicketPtr ticket = std::make_shared<Ticket>(movie, A, 11);
        BOOST_REQUIRE_THROW(TicketPtr ticket1 = std::make_shared<Ticket>(movie, A, 11),TicketException);
        BOOST_REQUIRE_THROW(TicketPtr ticket1 = std::make_shared<Ticket>(nullptr, B, 11),TicketException);
        BOOST_REQUIRE_THROW(TicketPtr ticket1 = std::make_shared<Ticket>(movie, A, 33),TicketException);
        BOOST_REQUIRE_THROW(TicketPtr ticket1 = std::make_shared<Ticket>(movie, Z, 32),TicketException);
    }
BOOST_AUTO_TEST_SUITE_END()