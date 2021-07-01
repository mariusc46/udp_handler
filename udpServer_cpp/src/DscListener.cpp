#include <chrono>
#include <limits>
#include <bits/stdc++.h>

#include "../libs/CRC.h"
#include "DscListener.hpp"
#include "Logger.hpp"


constexpr uint32_t NO_MESSAGE_LOGGED = std::numeric_limits<uint32_t>::max();

udp_listener::DscListener::DscListener(std::unique_ptr<Logger> logger): _previous_log_mileage(NO_MESSAGE_LOGGED), _logger(std::move(logger))
{
}

int64_t udp_listener::DscListener::getUnixTimestamp() noexcept
{
    int64_t microsecondsUTC =
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return microsecondsUTC;
}

float udp_listener::DscListener::convertSpeedToKmh(const float speed_ms) noexcept
{
    constexpr float msToKmhMultiplier = 3.6f;
    return (speed_ms * msToKmhMultiplier * 10U) / 10.0f;
}

uint16_t udp_listener::DscListener::getMessageId() noexcept
{
    uint16_t id = (_singleFrameBuffer[0] << 8U) | _singleFrameBuffer[1];
    return id;
};

bool udp_listener::DscListener::validateCrc() noexcept
{
    uint8_t crc = _singleFrameBuffer[9];
    uint8_t expected_crc = Crc_CalculateCRC8H2F(_singleFrameBuffer.data(), 9U, 0xff, true);

    return crc == expected_crc;
}

uint32_t udp_listener::DscListener::getMileage() noexcept
{
    uint32_t mileage = (uint32_t(_singleFrameBuffer[3]) << 16U) | (uint32_t(_singleFrameBuffer[4]) << 8U) | uint32_t(_singleFrameBuffer[5]);
    return mileage;
}

uint32_t udp_listener::DscListener::getSpeed() noexcept
{
    uint32_t speed = (uint32_t(_singleFrameBuffer[6]) << 16U) | (uint32_t(_singleFrameBuffer[7]) << 8U) | uint32_t(_singleFrameBuffer[8]);
    return speed;
}

bool udp_listener::DscListener::isTimeToLog(const uint32_t mileage) noexcept
{
    constexpr int log_required_interval = 10U;

    if (_previous_log_mileage == NO_MESSAGE_LOGGED || mileage == _previous_log_mileage + log_required_interval)
    {
        _previous_log_mileage = mileage;
        return true;
    }

    return false;
}

void udp_listener::DscListener::handleIncomingBuffer(const std::span<uint8_t> buffer)
{
    constexpr uint16_t DEFINED_NUMBER_OF_BYTES = 10U;
    constexpr uint16_t ONE_CAN_MESSAGE_SIZE = 10U;

    if (buffer.size() == ONE_CAN_MESSAGE_SIZE)
    {
        _singleFrameBuffer = buffer;
        handleOneCanFrame();
    }
    else // split UDP frame in smaller CAN frames
    {
        for (uint16_t bytes_index = 0U; bytes_index < buffer.size(); bytes_index += DEFINED_NUMBER_OF_BYTES)
        {
            _singleFrameBuffer = std::span<uint8_t>(buffer.data() + bytes_index, 10U);
            handleOneCanFrame();
        }
    }
}

void udp_listener::DscListener::handleOneCanFrame()
{
    constexpr bool VALID_CRC = true;
    constexpr uint16_t VALID_ID = 0x21A;

    if (getMessageId() == VALID_ID)
    {
        if (validateCrc() == VALID_CRC)
        {
            uint32_t mileage = getMileage();

            if (isTimeToLog(mileage))
            {
                uint32_t speed_ms = getSpeed();
                _logger->LogMessage(getUnixTimestamp(), mileage, convertSpeedToKmh(speed_ms));
            }
        }
        else
        {
            _logger->LogError();
        }
    }
}
