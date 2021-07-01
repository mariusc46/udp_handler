cmake_minimum_required(VERSION 3.10)
project(udp_listener VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(CTest)
enable_testing()

add_subdirectory(tests/googletest)

include_directories(include)
include_directories(tests/googletest/include)

add_executable(udp_listener src/main.cpp src/Logger.hpp src/Listener.hpp src/MyLogger.cpp src/MyLogger.hpp libs/Network.cpp libs/Network.h libs/CRC.cpp libs/CRC.h src/MyListener.cpp src/MyListener.hpp src/MyServer.cpp src/MyServer.hpp)

#add_executable(my_tests tests/test_MyLogger.cpp src/Listener.hpp src/MyLogger.cpp src/MyLogger.hpp)
add_executable(my_tests tests/test_MyListener.cpp src/Logger.hpp src/Listener.hpp src/MyLogger.cpp src/MyLogger.hpp libs/Network.cpp libs/Network.h libs/CRC.cpp libs/CRC.h src/MyListener.cpp src/MyListener.hpp src/MyServer.cpp src/MyServer.hpp)

target_link_libraries(my_tests PRIVATE gtest gmock)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
