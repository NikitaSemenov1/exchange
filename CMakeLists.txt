CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(ClienServerEcn)

FIND_PACKAGE(Boost 1.40 COMPONENTS system REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

SET(CMAKE_CXX_STANDARD 20)

ADD_EXECUTABLE(Server server.cpp core/common.hpp
        core/exchange.cpp
        core/account.cpp
        io/auth.hpp
        io/error.hpp
        io/common.hpp
        io/handler.cpp
        io/handler.hpp)
TARGET_LINK_LIBRARIES(Server PRIVATE Threads::Threads ${Boost_LIBRARIES})

ADD_EXECUTABLE(Client client.cpp core/common.hpp
        io/auth.hpp
        io/error.hpp
        io/common.hpp)
TARGET_LINK_LIBRARIES(Client PRIVATE Threads::Threads ${Boost_LIBRARIES})