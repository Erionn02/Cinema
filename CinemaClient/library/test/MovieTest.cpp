#include <boost/test/unit_test.hpp>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "Exceptions/MovieException.h"
#include "typedefs.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(MovieSuite)
    BOOST_AUTO_TEST_CASE(MovieGetterTests) {
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu = pt::ptime (gr::date(2023, 05,14), pt::hours(19)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        MoviePtr movie = std::make_shared<Movie>(1,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom,15);

        BOOST_TEST(movie->getTitle() == "NoWy FiLm");
        BOOST_TEST(movie->getStart() == pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30)));
        BOOST_TEST(movie->getEnd() == pt::ptime (gr::date(2023, 05,14), pt::hours(19)+pt::minutes(30)));
        BOOST_TEST(movie->getTime() == 120);
        BOOST_TEST(movie->getAgeRequired() == 13);
        BOOST_TEST(movie->getType() == "Przygodowy");
        BOOST_TEST(movie->getScreeningRoom()->getId() == 7);
}
    BOOST_AUTO_TEST_CASE(MovieInfoTests) {
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        MoviePtr movie = std::make_shared<Movie>(2,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom,20);
        BOOST_TEST_MESSAGE(movie->getMovieInfo());
}
    BOOST_AUTO_TEST_CASE(MovieExceptionTest) {
        pt::ptime startFilmu = pt::ptime (gr::date(2022,05,14), pt::hours(17)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        //BOOST_REQUIRE_THROW(MoviePtr movie = std::make_shared<Movie>(2,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom),MovieException);
        pt::ptime startFilmu2 = pt::ptime (gr::date(2023,05,22), pt::hours(21)+pt::minutes(30));
        BOOST_REQUIRE_THROW(MoviePtr movie = std::make_shared<Movie>(2,"NoWy FiLm", startFilmu2, -120, 13, "Przygodowy", screeningRoom),MovieException);
    }
BOOST_AUTO_TEST_SUITE_END()

