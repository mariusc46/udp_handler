#pragma once
#include <cstdint>

namespace logger
{
    class Logger
    {
    public:
        virtual ~Logger() noexcept = default;
        virtual void LogMessage(uint32_t mileage, float speed) = 0;
        virtual void LogError() = 0;
    };
}
