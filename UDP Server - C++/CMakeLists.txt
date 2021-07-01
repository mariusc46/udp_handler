cmake_minimum_required(VERSION 3.10)
project(udp_listener VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(CTest)
enable_testing()

add_subdirectory(tests/googletest)

include_directories(include)
include_directories(tests/googletest/include)

set (SOURCES src/main.cpp src/MyLogger.cpp libs/Network.cpp libs/CRC.cpp src/MyListener.cpp src/MyServer.cpp)
set (HEADERS src/Logger.hpp src/Listener.hpp src/MyLogger.hpp libs/Network.h libs/CRC.h src/MyListener.hpp src/MyServer.hpp)

add_executable(udp_listener ${SOURCES} ${HEADERS})

add_executable(tests_myLogger tests/test_MyLogger.cpp src/Listener.hpp src/MyLogger.cpp src/MyLogger.hpp)
add_executable(tests_myListener tests/test_MyListener.cpp src/Logger.hpp src/Listener.hpp src/MyLogger.cpp src/MyLogger.hpp libs/Network.cpp libs/Network.h libs/CRC.cpp libs/CRC.h src/MyListener.cpp src/MyListener.hpp src/MyServer.cpp src/MyServer.hpp)

target_link_libraries(tests_myLogger PRIVATE gtest gmock)
target_link_libraries(tests_myListener PRIVATE gtest gmock)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
