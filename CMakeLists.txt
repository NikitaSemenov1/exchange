CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(ClienServerEcn)

FIND_PACKAGE(Boost 1.40 COMPONENTS system REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

SET(CMAKE_CXX_STANDARD 20)

ADD_EXECUTABLE(Server Server.cpp core/Common.hpp json.hpp
        core/Exchange.cpp
        core/Account.cpp)
TARGET_LINK_LIBRARIES(Server PRIVATE Threads::Threads ${Boost_LIBRARIES})

ADD_EXECUTABLE(Client Client.cpp core/Common.hpp json.hpp)
TARGET_LINK_LIBRARIES(Client PRIVATE Threads::Threads ${Boost_LIBRARIES})