#include "Listener.hpp"
#include "UdpServer.hpp"
#include <array>

namespace udp_listener
{
    void UdpServerClass::receiveFrames()
    {
        std::array<uint8_t, 500> buffer;

        while (1)
        {
            int numberOfreceivedBytes = m_udpServer->recv(reinterpret_cast<char*>(buffer.data()), buffer.size());

            if (numberOfreceivedBytes > 0U)
            {
                m_listener->handleIncomingBuffer(std::span<uint8_t>(buffer.data(), numberOfreceivedBytes));
            }
        }
    }

    UdpServerClass::UdpServerClass(const std::string &ip, const uint16_t port, std::unique_ptr<interpreter::Listener> listener):
        m_udpServer(std::make_unique<udp_client_server::udp_server>(ip, port)), m_listener(std::move(listener))
    {
    }
}
