#pragma once
#include "../libs/Network.h"
#include "Interpreter.hpp"

#include <memory>

namespace udp_listener
{
    class Interpreter;

    class UdpListener
    {
    public:
        UdpListener(const std::string& ip, const uint16_t port, std::unique_ptr<interpreter::Interpreter> listener);
        void receiveFrames();

    private:
        std::unique_ptr<udp_client_server::udp_server> m_udpServer;
        std::unique_ptr<interpreter::Interpreter> m_listener;
    };
}
