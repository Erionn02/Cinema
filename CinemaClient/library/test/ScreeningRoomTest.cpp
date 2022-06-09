#include <boost/test/unit_test.hpp>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include <vector>
#include "Exceptions/CinemaException.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(ScreeningRoomSuite)

    BOOST_AUTO_TEST_CASE(ScreeningRoomTests){
        pt::ptime startFilmu = pt::ptime (gr::date(2032,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu = pt::ptime (gr::date(2032, 05,14), pt::hours(19)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        MoviePtr movie = std::make_shared<Movie>(1,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom,15);

        pt::ptime startFilmu1 = pt::ptime (gr::date(2042,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu1 = pt::ptime (gr::date(2042, 05,14), pt::hours(19)+pt::minutes(30));
        MoviePtr movie1 = std::make_shared<Movie>(2,"NoWy FiLm", startFilmu1, 120, 13, "Przygodowy", screeningRoom,15);
        screeningRoom->addMovie(movie);
        TicketPtr ticket1 = std::make_shared<Ticket>(movie, A, 11);
        BOOST_TEST(screeningRoom->canAdd(startFilmu1,koniecFilmu1));
        BOOST_TEST(screeningRoom->getSize() == 1);
        BOOST_REQUIRE_THROW(screeningRoom->getMovieIndex(movie1) == 1,CinemaException);
        BOOST_REQUIRE_NO_THROW(screeningRoom->addMovie(movie1));
        BOOST_TEST(screeningRoom->getSize() == 2);
        BOOST_TEST(screeningRoom->getMovies().size()==screeningRoom->getT().size());
        BOOST_REQUIRE_THROW(screeningRoom->addMovie(nullptr),CinemaException);
        BOOST_TEST(!screeningRoom->isSeatValid(A,11,movie));
        BOOST_REQUIRE_NO_THROW(screeningRoom->deleteMovie(movie));
        BOOST_REQUIRE_THROW(screeningRoom->deleteMovie(nullptr),CinemaException);
        BOOST_TEST(screeningRoom->getSize() == 1);
        BOOST_TEST(screeningRoom->getMovies().size()==screeningRoom->getT().size());
        BOOST_TEST_MESSAGE(screeningRoom->getMoviesInfo());
        BOOST_TEST(screeningRoom->getId()==7);
        BOOST_REQUIRE_THROW(screeningRoom->getMovieIndex(nullptr),CinemaException);
    }

BOOST_AUTO_TEST_SUITE_END()