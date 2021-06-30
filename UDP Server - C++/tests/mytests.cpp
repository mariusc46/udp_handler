#include "../src/MyLogger.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MyLoggerMock: udp_listener::MyLogger
{
    // METHOD();
};

class MyTestLogger: testing::Test
{
public:
    udp_listener::MyLogger testObj;
};

TEST_F(MyTestLogger, log_error)
{
    testing::internal::CaptureStdout();
    testObj.LogError();

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("CRC"), std::string::npos);
}

TEST(MyTestLogger, log_message)
{
    testObj.LogMessage(123456, 123, 32.5f);

    EXPECT_EQ(1, 1);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}