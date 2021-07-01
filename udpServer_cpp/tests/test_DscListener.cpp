#include <gmock/gmock.h>
#include <gtest/gtest.h>

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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
