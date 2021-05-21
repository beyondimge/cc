cmake_minimum_required(VERSION 3.0.0)
project(ccpp VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("ccpp/include" "ccpp/src")

FIND_PACKAGE(Boost)
message(STATUS "BOOST_ROOT=${BOOST_ROOT}")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
include_directories(${HOME}/boost_1_75_0/)
find_package(Boost 1.65.0 REQUIRED COMPONENTS date_time)



add_executable(
    a.out
    ./ccpp/src/main.cpp 
    ./ccpp/src/game.cpp 
    ./ccpp/src/gameboard.cpp 
    ./ccpp/src/player.cpp 
    ./ccpp/src/card.cpp 
    ./ccpp/src/deck.cpp
    ./ccpp/src/utils.cpp
    ./ccpp/src/event.cpp
    ./ccpp/src/input.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
