#pragma once
#include "Listener.hpp"

#include <span>
#include <memory>

namespace udp_listener
{
    class Logger;
    class DscListener: public Listener
    {
    public:
        DscListener(std::unique_ptr<Logger> logger);
        virtual void handleIncomingBuffer(const std::span<uint8_t> buffer);

    protected:
        static float convertSpeedToKmh(const float speed_ms) noexcept;
        bool isTimeToLog(const uint32_t mileage) noexcept;
        uint32_t _previous_log_mileage;

    private:
        uint16_t getMessageId() noexcept;
        uint32_t getMileage() noexcept;
        uint32_t getSpeed() noexcept;
        static int64_t getUnixTimestamp() noexcept;
        void handleOneCanFrame();
        bool validateCrc() noexcept;

        std::span<uint8_t> _singleFrameBuffer;
        std::unique_ptr<Logger> _logger;
    };
}
