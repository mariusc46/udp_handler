cmake_minimum_required(VERSION 3.10)
project(udp_listener VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include_directories(include)

set (SOURCES CsvLogger.cpp ../libs/Network.cpp ../libs/CRC.cpp DscInterpreter.cpp UdpListener.cpp)
set (HEADERS Logger.hpp Listener.hpp CsvLogger.hpp ../libs/Network.h ../libs/CRC.h DscInterpreter.hpp UdpListener.hpp setup.hpp)

add_executable(udp_listener ${SOURCES} ${HEADERS} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
