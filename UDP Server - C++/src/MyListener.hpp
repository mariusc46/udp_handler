#include "../libs/Network.h"
#include "Listener.hpp"

#include <span>

namespace udp_listener
{
    class MyListener: public udp_listener::Listener
    {
    public:
        MyListener();
        virtual void handleIncomingBuffer(const std::span<uint8_t> buffer);

    protected:
        static float convertSpeedToKmh(const float speed_ms) noexcept;
        uint16_t getMessageId() noexcept;
        uint32_t getMileage() noexcept;
        uint32_t getSpeed() noexcept;
        static int64_t getUnixTimestamp() noexcept;
        void handleOneCanFrame();
        bool isTimeToLog(const uint32_t mileage) noexcept;
        bool validateCrc() noexcept;

    private:
        uint32_t _previous_log_mileage;
        std::span<uint8_t> _incommingBuffer;
        std::span<uint8_t> _singleFrameBuffer;
    };
}
