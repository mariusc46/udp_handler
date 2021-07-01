cmake_minimum_required(VERSION 3.10)
project(udp_listener VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(CTest)
enable_testing()

add_subdirectory(tests/googletest)

include_directories(include)
include_directories(tests/googletest/include)

set (SOURCES src/CsvLogger.cpp libs/Network.cpp libs/CRC.cpp src/DscListener.cpp src/MyServer.cpp)
set (HEADERS src/Logger.hpp src/Listener.hpp src/CsvLogger.hpp libs/Network.h libs/CRC.h src/DscListener.hpp src/MyServer.hpp)

add_executable(udp_listener ${SOURCES} ${HEADERS} src/main.cpp)
#add_executable(tests_myLogger ${SOURCES} ${HEADERS} tests/test_MyLogger.cpp)
add_executable(tests_myListener ${SOURCES} ${HEADERS} tests/test_MyListener.cpp)

#target_link_libraries(tests_myLogger PRIVATE gtest gmock)
target_link_libraries(tests_myListener PRIVATE gtest gmock)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
