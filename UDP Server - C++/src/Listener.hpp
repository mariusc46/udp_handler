#include "MyLogger.hpp"

#include <span>

namespace udp_listener
{
    class Listener
    {
    public:
        virtual void handleIncomingBuffer(const std::span<uint8_t> buffer) = 0;
        udp_listener::MyLogger myLogObj;
    };
}
