#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include <memory>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include "model/Client.h"
#include <boost/date_time.hpp>
#include "Exceptions/CinemaException.h"
#include "managers/MovieManager.h"
#include "Exceptions/ScreeningRoomException.h"
#include "managers/ScreeningRoomManager.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(ScreeningRoomManagerSuite)

    BOOST_AUTO_TEST_CASE(ScreeningRoomManagerTests) {
        ScreeningRoomManager SM;
        ScreeningRoomPtr s1 = SM.addScreeningRoom(1);
        BOOST_TEST(SM.getSize()==1);
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        MovieManager MM;
        MoviePtr m1 = MM.addMovie(2137,"Titanic",startFilmu,120,18,"Dramat",s1,20);
        ScreeningRoomPtr s2 = SM.addScreeningRoom(2);
        ScreeningRoomPtr s3 = SM.addScreeningRoom(3);
        BOOST_TEST(SM.getSize()==3);
        SM.deleteScreeningRoom(s3);
        BOOST_TEST(SM.getSize()==2);
        BOOST_TEST(SM.findById(1)==s1);
        BOOST_TEST(SM.getScreeningRoomMovies(s1).size()==1);
        BOOST_TEST_MESSAGE(SM.getScreeningRoomInfo(s1));
        BOOST_TEST_MESSAGE(SM.getScreeningRoomsInfo());
}
    BOOST_AUTO_TEST_CASE(ScreeningRoomExceptionsTest)
    {
        ScreeningRoomManager SM;
        BOOST_REQUIRE_THROW(SM.deleteScreeningRoom(nullptr),ScreeningRoomException);
        BOOST_REQUIRE_THROW(SM.getScreeningRoomInfo(nullptr),ScreeningRoomException);
        BOOST_REQUIRE_THROW(SM.getScreeningRoomMovies(nullptr),ScreeningRoomException);
    }
BOOST_AUTO_TEST_SUITE_END()

