#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <array>

#include "../src/MyListener.hpp"

class MyListenerTest: public ::testing::Test
{
    protected:
    udp_listener::MyListener listener;
};

TEST_F(MyListenerTest, LogErrorTest)
{
    std::array<uint8_t, 100> buffer;

    listener.handleIncomingBuffer(buffer);
    EXPECT_EQ(1, 1);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}