#pragma once
#include <cstdint>

namespace udp_listener
{
    class Logger
    {
    public:
        virtual ~Logger() noexcept = default;
        virtual void LogMessage(uint32_t mileage, float speed) = 0;
        virtual void LogError() = 0;
    };
}
