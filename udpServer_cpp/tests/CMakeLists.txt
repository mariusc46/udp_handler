cmake_minimum_required(VERSION 3.10)
project(udp_listener VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(CTest)
enable_testing()

add_subdirectory(googletest)

include_directories(include)
include_directories(tests/googletest/include)

add_executable(tests_CsvLogger test_CsvLogger.cpp ../src/CsvLogger.cpp ../src/CsvLogger.hpp)
add_executable(tests_DscInterpreter tests_DscInterpreter.cpp mock.hpp ../src/DscInterpreter.cpp ../src/DscInterpreter.hpp ../src/CsvLogger.cpp ../src/CsvLogger.hpp ../libs/CRC.cpp ../libs/CRC.h ../src/setup.hpp)

target_link_libraries(tests_CsvLogger PRIVATE gtest gmock)
target_link_libraries(tests_DscInterpreter PRIVATE gtest gmock)

target_compile_definitions(tests_DscInterpreter PRIVATE UNIT_TEST_ENABLE=1)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
