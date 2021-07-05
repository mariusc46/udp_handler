#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/CsvLogger.hpp"
#include "../src/DscInterpreter.hpp"
#include "mock.hpp"

TEST(DscInterpreterTest, isTimeToLog)
{
    auto myDscInterpreter = interpreter::DscInterpreter(std::make_unique<LoggerMock>());
    myDscInterpreter.m_previous_log_mileage = 0;
    EXPECT_EQ(true, myDscInterpreter.isTimeToLog(10));
}

TEST(DscInterpreterTest, convertSpeedToKmh)
{
    auto myDscInterpreter = interpreter::DscInterpreter(std::make_unique<LoggerMock>());

    float computedSpeedInKmh = myDscInterpreter.convertSpeedToKmh(10);
    EXPECT_EQ(computedSpeedInKmh, 36);
}

TEST(DscInterpreterTest, handleIncomingBuffer)
{
    LoggerMock mock;
    std::array<uint8_t, 100> test_buffer = {0x02, 0x1a, 0x08, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1C};

    auto myDscInterpreter = interpreter::DscInterpreter(std::make_unique<LoggerMock>());

    EXPECT_CALL(mock, LogError()).Times(1);
    myDscInterpreter.handleIncomingBuffer(test_buffer);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
