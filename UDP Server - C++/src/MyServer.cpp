#include "MyServer.hpp"
#include <array>

void udp_listener::MyServerClass::receiveFrames()
{
    std::array<uint8_t, 100> buffer;

    while (1)
    {
        int numberOfreceivedBytes = myUdpServer->recv(reinterpret_cast<char*>(buffer.data()), buffer.size());

        if (numberOfreceivedBytes > 0U)
        {
            myListenObj.handleIncomingBuffer(std::span<uint8_t>(buffer.data(), numberOfreceivedBytes));
        }
    }
}

udp_listener::MyServerClass::MyServerClass(const std::string ip, const int port):
    myUdpServer(std::make_unique<udp_client_server::udp_server>(ip, port))
{
}
