#pragma once
#include <span>
#include <cstdint>

namespace interpreter
{
    class Interpreter
    {
    public:
        virtual ~Interpreter() noexcept = default;
        virtual void handleIncomingBuffer(const std::span<uint8_t> buffer) = 0;
    };
}
