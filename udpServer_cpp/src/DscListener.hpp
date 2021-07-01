#pragma once
#include "Listener.hpp"

#include <memory>
#include <span>

#if defined UNIT_TEST_ENABLE
    #define Private public
#else
    #define Private private
#endif

namespace udp_listener
{
    class Logger;
    class DscListener: public Listener
    {
    public:
        DscListener(std::unique_ptr<Logger> logger);
        virtual ~DscListener() = default;
        virtual void handleIncomingBuffer(const std::span<uint8_t> buffer);

    Private:
        static float convertSpeedToKmh(const float speed_ms) noexcept;
        bool isTimeToLog(const uint32_t mileage) noexcept;
        uint16_t getMessageId() noexcept;
        uint32_t getMileage() noexcept;
        uint32_t getSpeed() noexcept;
        static int64_t getUnixTimestamp() noexcept;
        void handleOneCanFrame();
        bool validateCrc() noexcept;

        std::span<uint8_t> m_singleFrameBuffer;
        std::unique_ptr<Logger> m_logger;
        uint32_t m_previous_log_mileage;
    };
}
