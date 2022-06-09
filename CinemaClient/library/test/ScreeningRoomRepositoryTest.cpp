#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include <memory>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include <boost/date_time.hpp>
#include "repositories/ScreeningRoomRepository.h"
#include "Exceptions/CinemaException.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(ScreeningRoomRepositorySuite)

    BOOST_AUTO_TEST_CASE(ScreeningRoomRepositoryTests){
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu = pt::ptime (gr::date(2023, 05,14), pt::hours(19)+pt::minutes(30));
        pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu2 = pt::ptime (gr::date(2033, 05,14), pt::hours(19)+pt::minutes(30));
        int id=7;
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(id);
        ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
        std::string title="tytul";
        MoviePtr movie = std::make_shared<Movie>(1,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom,15);
        MoviePtr movie1 = std::make_shared<Movie>(2,title, startFilmu2, 120, 16, "Akcji", screeningRoom1,5);
        screeningRoom->addMovie(movie);
        screeningRoom1->addMovie(movie1);
        TicketPtr ticket = std::make_shared<Ticket>(movie, A, 10);
        TicketPtr ticket1 = std::make_shared<Ticket>(movie, A, 11);
        TicketPtr ticket2 = std::make_shared<Ticket>(movie1, D, 17);
        ScreeningRoomRepository SR;
        SR.add(screeningRoom);
        SR.add(screeningRoom1);

        BOOST_TEST(SR.getSize()==2);
        BOOST_TEST(SR.findAll().size()==2);
        BOOST_TEST(SR.getRepository().size()==SR.getSize());
        std::function<bool(std::shared_ptr<ScreeningRoom>)> f=[id](std::shared_ptr<ScreeningRoom> obj)->bool
        {
            return obj->getId()==id;
        };
        BOOST_TEST_MESSAGE(SR.getObjectsInfo());
        BOOST_TEST(SR.findBy(f).size()==1);
        BOOST_TEST(SR.findBy(f)[0]==screeningRoom);
        BOOST_TEST(SR.getObjectInfo(screeningRoom)==screeningRoom->getInfo());
        SR.remove(screeningRoom);
        BOOST_REQUIRE(SR.getSize()==1);
        BOOST_TEST(SR.getObject(5)==screeningRoom1);
        BOOST_TEST(SR.getObjectByIndex(0)==screeningRoom1);
    }

    BOOST_AUTO_TEST_CASE(ScreeningRoomRepositoryExceptionsTest){
        ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
        ScreeningRoomRepository SR;

        BOOST_REQUIRE_THROW(SR.add(nullptr),CinemaException);
        BOOST_REQUIRE_THROW(SR.remove(nullptr),CinemaException);
        BOOST_REQUIRE_THROW(SR.remove(screeningRoom1),CinemaException);
        BOOST_REQUIRE_THROW(SR.getObjectByIndex(0),CinemaException);
        BOOST_REQUIRE_THROW(SR.getObjectByIndex(-1),CinemaException);
        BOOST_REQUIRE_THROW(SR.getObjectInfo(nullptr),CinemaException);
        SR.add(screeningRoom1);
        BOOST_REQUIRE_THROW(SR.add(screeningRoom1),CinemaException);
    }
BOOST_AUTO_TEST_SUITE_END()

