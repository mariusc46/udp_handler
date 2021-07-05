#pragma once
#include <span>
#include <cstdint>

namespace interpreter
{
    class Listener
    {
    public:
        virtual ~Listener() noexcept = default;
        virtual void handleIncomingBuffer(const std::span<uint8_t> buffer) = 0;
    };
}
