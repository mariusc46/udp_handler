cmake_minimum_required(VERSION 3.10)
project(udp_listener VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(CTest)
enable_testing()

add_subdirectory(googletest)

include_directories(include)
include_directories(tests/googletest/include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS} -g")

add_executable(tests_CsvLogger test_CsvLogger.cpp ../src/CsvLogger.cpp ../src/CsvLogger.hpp)
add_executable(tests_DscListener test_DscListener.cpp mock.hpp ../src/DscListener.cpp ../src/DscListener.hpp ../src/CsvLogger.cpp ../src/CsvLogger.hpp ../libs/CRC.cpp ../libs/CRC.h ../src/setup.hpp)

target_link_libraries(tests_CsvLogger PRIVATE gtest gmock)
target_link_libraries(tests_DscListener PRIVATE gtest gmock)

target_compile_definitions(tests_DscListener PRIVATE UNIT_TEST_ENABLE=1)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
