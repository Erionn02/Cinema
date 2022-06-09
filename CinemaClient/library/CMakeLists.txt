cmake_minimum_required(VERSION 3.4)
project(BibliotekaKina)

set(SOURCE_FILES
        src/model/Movie.cpp
        src/model/Ticket.cpp
        src/model/ScreeningRoom.cpp
        src/repositories/ClientRepository.cpp
        src/repositories/MovieRepository.cpp
        src/repositories/ScreeningRoomRepository.cpp
        src/model/Client.cpp
        src/model/ClientType.cpp
        src/model/Junior.cpp
        src/model/Regular.cpp
        src/model/Senior.cpp
        src/model/Concessionary.cpp
        src/managers/ClientManager.cpp
        src/managers/MovieManager.cpp
        src/managers/ScreeningRoomManager.cpp
        src/Exceptions/CinemaException.cpp
        src/Exceptions/TicketException.cpp
        src/Exceptions/ClientException.cpp
        src/Exceptions/MovieException.cpp
        src/Exceptions/ScreeningRoomException.cpp
        src/ServerStuff/functions.cpp
        src/GUI/MyApp.cpp
        src/GUI/MainFrame.cpp
        src/GUI/RegisterFrame.cpp
        src/GUI/MyFrame.cpp
        src/GUI/AdminLogin.cpp
        src/GUI/AdminPanel.cpp
        src/GUI/AdminMoviesFrame.cpp
        src/GUI/AdminUsersFrame.cpp
        src/GUI/AdminRoomsFrame.cpp
        src/GUI/UserLoginFrame.cpp
        src/GUI/UserPanel.cpp
        src/GUI/AdminAddMovie.cpp
        src/GUI/Calendar.cpp
        src/GUI/CalendarFrame.cpp
        src/GUI/AdminAddRoom.cpp
        src/GUI/AdminConfirmDeleteRoom.cpp
        src/GUI/AdminConfirmDeleteMovie.cpp
        src/GUI/AdminConfirmUnregisterUser.cpp
        src/GUI/BuyTicketFrame.cpp
        src/GUI/UserAddMoney.cpp
        src/GUI/UserUnregister.cpp
        )

set(wxWidgets_ROOT_DIR </usr/include/wx-3.0-unofficial>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})


add_library(BibliotekaKina ${SOURCE_FILES})

target_include_directories(BibliotekaKina PUBLIC include)

enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
../library/test/master.cpp
../library/test/ClientRepositoryTest.cpp
../library/test/MovieRepositoryTest.cpp
../library/test/ScreeningRoomRepositoryTest.cpp
../library/test/TicketTest.cpp
        ../library/test/ScreeningRoomTest.cpp
        ../library/test/MovieTest.cpp
../library/test/ClientTest.cpp
        ../library/test/ClientManagerTest.cpp
../library/test/ScreeningRoomManagerTest.cpp
        test/MovieManagerTest.cpp)




add_executable (TestOfModelClasses ${SOURCE_TEST_FILES})


target_link_libraries (TestOfModelClasses
        BibliotekaKina
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )


add_test(TestOfModelClassesExec TestOfModelClasses
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )