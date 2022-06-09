#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include <memory>
#include "model/ScreeningRoom.h"
#include "model/Movie.h"
#include "model/Ticket.h"
#include <boost/date_time.hpp>
#include "repositories/MovieRepository.h"
#include "Exceptions/CinemaException.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(MovieRepositorySuite)

    BOOST_AUTO_TEST_CASE(MovieRepositoryTests){
        pt::ptime startFilmu = pt::ptime (gr::date(2023,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu = pt::ptime (gr::date(2023, 05,14), pt::hours(19)+pt::minutes(30));
        pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu2 = pt::ptime (gr::date(2033, 05,14), pt::hours(19)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom = std::make_shared<ScreeningRoom>(7);
        ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
        std::string title="tytul";
        MoviePtr movie = std::make_shared<Movie>(1,"NoWy FiLm", startFilmu, 120, 13, "Przygodowy", screeningRoom,25);
        MoviePtr movie1 = std::make_shared<Movie>(2,title, startFilmu2, 120, 16, "Akcji", screeningRoom1,30);
        screeningRoom->addMovie(movie);
        screeningRoom1->addMovie(movie1);
        TicketPtr ticket = std::make_shared<Ticket>(movie, A, 10);
        TicketPtr ticket1 = std::make_shared<Ticket>(movie, A, 11);
        TicketPtr ticket2 = std::make_shared<Ticket>(movie1, D, 17);
        MovieRepository MR;
        MR.add(movie);
        MR.add(movie1);
        BOOST_TEST(MR.getSize()==2);
        BOOST_TEST(MR.findAll().size()==2);
        BOOST_TEST(MR.getRepository().size()==MR.getSize());
        std::function<bool(std::shared_ptr<Movie>)> f=[title](std::shared_ptr<Movie> obj)->bool
        {
            return obj->getTitle()==title;
        };
        BOOST_TEST_MESSAGE(MR.getObjectsInfo());
        BOOST_TEST(MR.findBy(f).size()==1);
        BOOST_TEST(MR.findBy(f)[0]==movie1);
        BOOST_TEST(MR.getObjectInfo(movie)==movie->getInfo());
        MR.remove(movie);
        BOOST_REQUIRE(MR.getSize()==1);
        BOOST_TEST(MR.getObject(2)==movie1);
        BOOST_TEST(MR.getObjectByIndex(0)==movie1);
    }

    BOOST_AUTO_TEST_CASE(MovieRepositoryExceptionsTest){
        pt::ptime startFilmu2 = pt::ptime (gr::date(2033,05,14), pt::hours(17)+pt::minutes(30));
        pt::ptime koniecFilmu2 = pt::ptime (gr::date(2033, 05,14), pt::hours(19)+pt::minutes(30));
        ScreeningRoomPtr screeningRoom1 = std::make_shared<ScreeningRoom>(5);
        MoviePtr movie1 = std::make_shared<Movie>(2,"Tytul", startFilmu2, 120, 16, "Akcji", screeningRoom1,10);
        MovieRepository MR;

        BOOST_REQUIRE_THROW(MR.add(nullptr),CinemaException);
        BOOST_REQUIRE_THROW(MR.remove(nullptr),CinemaException);
        BOOST_REQUIRE_THROW(MR.remove(movie1),CinemaException);
        BOOST_REQUIRE_THROW(MR.getObjectByIndex(0),CinemaException);
        BOOST_REQUIRE_THROW(MR.getObjectByIndex(-1),CinemaException);
        BOOST_REQUIRE_THROW(MR.getObjectInfo(nullptr),CinemaException);
        MR.add(movie1);
        BOOST_REQUIRE_THROW(MR.add(movie1),CinemaException);
    }
BOOST_AUTO_TEST_SUITE_END()

