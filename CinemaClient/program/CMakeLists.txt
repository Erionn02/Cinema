cmake_minimum_required(VERSION 3.4)

project(Program)
set(wxWidgets_ROOT_DIR </usr/include/wx-3.0-unofficial>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES
        src/main.cpp)


add_executable(Program ${SOURCE_FILES})


target_link_libraries(Program BibliotekaKina)
target_link_libraries(Program ${wxWidgets_LIBRARIES})


target_include_directories(Program PUBLIC include)
enable_testing()
