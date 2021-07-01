#pragma once
#include <span>
#include <cstdint>

namespace udp_listener
{
    class Listener
    {
    public:
        virtual ~Listener() noexcept = default;
        virtual void handleIncomingBuffer(const std::span<uint8_t> buffer) = 0;
    };
}
