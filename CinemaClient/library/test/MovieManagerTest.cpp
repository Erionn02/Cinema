#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include <memory>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include <boost/date_time.hpp>
#include "Exceptions/CinemaException.h"
#include "Exceptions/MovieException.h"
#include "managers/MovieManager.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(MovieManagerSuite)

    BOOST_AUTO_TEST_CASE(MovieManagerTests) {
    pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
    pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
    ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
    MovieManager MM;
    int id=1;
    MoviePtr m1 = MM.addMovie(id,"Tytul", startFilmu2, 120, 16, "Akcji", screeningRoom1,25);
    MoviePtr m2 = MM.addMovie(2,"NoWy FiLm", startFilmu, 120,  13, "Przygodowy", screeningRoom1,30);

    BOOST_TEST(screeningRoom1->getSize()==2);
    BOOST_REQUIRE(MM.getSize()==2);
    BOOST_TEST(MM.getMovie(2)==m2);
    MoviePredicate predicate1 = [](MoviePtr m)->bool{
        return true;
    };
    BOOST_TEST(MM.findMovies(predicate1).size()==2);
    MoviePredicate predicate2 = [id](MoviePtr m)->bool{
        return m->getId()==id;
    };
    BOOST_TEST(MM.findMovies(predicate2).size()==1);
    MM.endMovie(m2);
    BOOST_TEST(MM.getMovie(2,false)==m2);
    BOOST_REQUIRE(MM.getSize(false)==1);
    BOOST_REQUIRE(MM.getSize()==1);
    BOOST_TEST(screeningRoom1->getSize()==1);

    }
    BOOST_AUTO_TEST_CASE(MovieManagerExceptionsTest)
    {
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime startFilmu3 = pt::ptime (gr::date(2013,05,14), pt::hours(17)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
        MovieManager MM;
        int id=1;
        MoviePtr m1 = MM.addMovie(id,"Tytul", startFilmu, 120, 16, "Akcji", screeningRoom1,30);
        BOOST_REQUIRE_THROW(MoviePtr m2 = MM.addMovie(2,"NoWy FiLm", startFilmu, 120,  13, "Przygodowy", screeningRoom1,10),MovieException);
        BOOST_REQUIRE_THROW(MoviePtr m2 = MM.addMovie(2,"NoWy FiLm", startFilmu2, 120,  13, "Przygodowy", nullptr,10),MovieException);
        BOOST_REQUIRE_THROW(MoviePtr m2 = MM.addMovie(2,"NoWy FiLm", startFilmu3, 120,  13, "Przygodowy", screeningRoom1,10),MovieException);
        BOOST_REQUIRE_THROW(MM.endMovie(nullptr),MovieException);
        pt::ptime startFilmu4 = pt::ptime (gr::date(2053,05,14), pt::hours(17)+pt::minutes(30));
        MoviePtr m3 = std::make_shared<Movie>(3,"Jakis film",startFilmu4,50,10,"Akcji",screeningRoom1,15);
        BOOST_REQUIRE_THROW(MM.endMovie(m3),CinemaException);
        BOOST_REQUIRE_THROW(MM.getMovieInfo(nullptr),CinemaException);
    }
BOOST_AUTO_TEST_SUITE_END()