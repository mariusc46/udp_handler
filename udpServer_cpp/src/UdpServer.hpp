#pragma once
#include "../libs/Network.h"

#include <memory>

namespace udp_listener
{
    class Listener;

    class UdpServerClass
    {
    public:
        UdpServerClass(const std::string& ip, const uint16_t port, std::unique_ptr<Listener> listener);
        void receiveFrames();

    private:
        std::unique_ptr<udp_client_server::udp_server> m_udpServer;
        std::unique_ptr<Listener> m_listener;
    };
}
