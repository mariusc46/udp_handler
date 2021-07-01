#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/MyLogger.hpp"

TEST(MyLogger, LogError)
{
    udp_listener::MyLogger logger;

    testing::internal::CaptureStderr();
    logger.LogError();
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("CRC"), std::string::npos);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}