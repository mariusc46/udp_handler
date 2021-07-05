#pragma once
#include "../libs/Network.h"
#include "Listener.hpp"

#include <memory>

namespace udp_listener
{
    class Listener;

    class UdpListener
    {
    public:
        UdpListener(const std::string& ip, const uint16_t port, std::unique_ptr<interpreter::Listener> listener);
        void receiveFrames();

    private:
        std::unique_ptr<udp_client_server::udp_server> m_udpServer;
        std::unique_ptr<interpreter::Listener> m_listener;
    };
}
