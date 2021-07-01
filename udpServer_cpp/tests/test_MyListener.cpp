#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/DscListener.hpp"

struct IsTimeToLogStruct
{
    float previousLogMileage;
    float currentLogMileage;
    bool returnValue;
};

class MyListenerTest: public udp_listener::DscListener, public ::testing::TestWithParam<IsTimeToLogStruct>
{
};

TEST_P(MyListenerTest, isTimeToLog)
{
    IsTimeToLogStruct testParams = GetParam();
    _previous_log_mileage = testParams.previousLogMileage;
    EXPECT_EQ(testParams.returnValue, isTimeToLog(testParams.currentLogMileage));
}

TEST_F(MyListenerTest, convertSpeedToKmh)
{
    float computedSpeedInKmh = convertSpeedToKmh(10);
    EXPECT_EQ(computedSpeedInKmh, 36);
}

INSTANTIATE_TEST_CASE_P(MyListenerTest, MyListenerTest, ::testing::Values(IsTimeToLogStruct(0, 9, false), (0, 10, true), (0, 11, false)));

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
