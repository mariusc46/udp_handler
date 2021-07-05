#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/CsvLogger.hpp"
#include "../src/DscListener.hpp"
#include "mock.hpp"

TEST(DscListenerTest, isTimeToLog)
{
    auto myDscListener = udp_listener::DscListener(std::make_unique<LoggerMock>());
    myDscListener.m_previous_log_mileage = 0;
    EXPECT_EQ(true, myDscListener.isTimeToLog(10));
}

TEST(DscListenerTest, convertSpeedToKmh)
{
    auto myDscListener = udp_listener::DscListener(std::make_unique<LoggerMock>());

    float computedSpeedInKmh = myDscListener.convertSpeedToKmh(10);
    EXPECT_EQ(computedSpeedInKmh, 36);
}

TEST(DscListenerTest, handleIncomingBuffer)
{
    LoggerMock mock;
    // auto myDscListener = udp_listener::DscListener(std::make_unique<udp_listener::CsvLogger>(std::move(mock)));

    //auto myLogger = std::make_unique<udp_listener::CsvLogger>();
    //auto myDscListener = std::make_unique<udp_listener::DscListener>(mock);

    // auto dep = std::make_unique<LoggerMock()>;

    // EXPECT_CALL(*dep, LogError()).Times(1);

    // std::array<uint8_t, 100> test_buffer = {0x02, 0x1a, 0x08, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1C};

    // //EXPECT_CALL(mock, LogError()).Times(1);

    // auto myDscListener = udp_listener::DscListener(std::make_unique<LoggerMock>(std::move(dep)));
   
    // //myDscListener.inject(std::move(dep));

    // myDscListener.handleIncomingBuffer(test_buffer);

    // EXPECT_CA L(1, 36);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
