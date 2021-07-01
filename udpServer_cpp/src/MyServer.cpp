#include "Listener.hpp"
#include "MyServer.hpp"
#include <array>

void udp_listener::MyServerClass::receiveFrames()
{
    std::array<uint8_t, 100> buffer;

    while (1)
    {
        int numberOfreceivedBytes = _udpServer->recv(reinterpret_cast<char*>(buffer.data()), buffer.size());

        if (numberOfreceivedBytes > 0U)
        {
            _listener->handleIncomingBuffer(std::span<uint8_t>(buffer.data(), numberOfreceivedBytes));
        }
    }
}

udp_listener::MyServerClass::MyServerClass(const std::string &ip, const uint16_t port, std::unique_ptr<Listener> listener):
    _udpServer(std::make_unique<udp_client_server::udp_server>(ip, port)), _listener(std::move(listener))
{
}