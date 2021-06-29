#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>

#include "../libs/CRC.h"
#include "MyListener.hpp"
#include <bits/stdc++.h>

const uint32_t NO_MESSAGE_LOGGED = std::numeric_limits<uint32_t>::max();

udp_listener::MyListener::MyListener(): _previous_log_mileage(NO_MESSAGE_LOGGED)
{
}

int64_t udp_listener::MyListener::getUnixTimestamp() noexcept
{
    int64_t microsecondsUTC =
    std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return microsecondsUTC;
}

float udp_listener::MyListener::convertSpeedToKmh(const float speed_ms) noexcept
{
    const float msToKmhMultiplier = 3.6f;
    return (speed_ms * msToKmhMultiplier * 10U) / 10.0f;
}

uint16_t udp_listener::MyListener::getMessageId() noexcept
{
    uint16_t id = (_singleFrameBuffer[0] << 8U) | _singleFrameBuffer[1];
    // std::cout << " ID " << std::hex << unsigned(id);
    return id;
};

bool udp_listener::MyListener::validateCrc() noexcept
{
    uint8_t crc = _singleFrameBuffer[9];
    uint8_t expected_crc = Crc_CalculateCRC8H2F(_singleFrameBuffer.data(), 9U, 0xff, true);

    return crc == expected_crc;
}

uint32_t udp_listener::MyListener::getMileage() noexcept
{
    uint32_t mileage = (uint32_t) ((_singleFrameBuffer[3] << 16U) | (_singleFrameBuffer[4] << 8U) | _singleFrameBuffer[5]);
    // std::cout << " mileage " << std::hex << unsigned(mileage);
    return mileage;
}

uint32_t udp_listener::MyListener::getSpeed() noexcept
{
    uint32_t speed = (uint32_t) ((_singleFrameBuffer[6] << 16U) | (_singleFrameBuffer[7] << 8U) | _singleFrameBuffer[8]);
    // std::cout << " speed " << std::hex << unsigned(speed);
    return speed;
}

bool udp_listener::MyListener::isTimeToLog(const uint32_t mileage) noexcept
{
    const int log_required_interval = 10U;

    if (_previous_log_mileage == NO_MESSAGE_LOGGED || mileage == _previous_log_mileage + log_required_interval)
    {
        _previous_log_mileage = mileage;
        return true;
    }

    return false;
}

void udp_listener::MyListener::handleIncomingBuffer(const std::span<uint8_t> buffer)
{
    const uint16_t DEFINED_NUMBER_OF_BYTES = 10U;
    const uint16_t ONE_CAN_MESSAGE_SIZE = 10U;

    _incommingBuffer = buffer;

    std::cout << "Number of received bytes: " << _incommingBuffer.size() << " | ";

    if (_incommingBuffer.size() == ONE_CAN_MESSAGE_SIZE)
    {
        _singleFrameBuffer = buffer;
        handleOneCanFrame();
    }
    else // split UDP frame in smaller CANr frames
    {
        // loop through received bytes and copy 10 entries in a temporary buffer
        for (uint16_t bytes_index = 0U; bytes_index < _incommingBuffer.size(); bytes_index += DEFINED_NUMBER_OF_BYTES)
        {
            _singleFrameBuffer = std::span<uint8_t>(buffer.data() + bytes_index, 10U);
            handleOneCanFrame();
        }
    }
}

void udp_listener::MyListener::handleOneCanFrame()
{
    const bool VALID_CRC = true;
    const uint16_t VALID_ID = 0x21A;

    if (getMessageId() == VALID_ID)
    {
        if (validateCrc() == VALID_CRC)
        {
            uint32_t mileage = getMileage();
            uint32_t speed_ms = getSpeed();

            if (isTimeToLog(mileage))
            {
                myLogObj.LogMessage(getUnixTimestamp(), mileage, convertSpeedToKmh(speed_ms));
            }
            else
            {
                std::cout << "Mileage value skiped for logging .. \n";
            }
        }
        else
        {
            myLogObj.LogError();
        }
    }
    else
    {
        std::cout << "Message ID not recognised, frame discarded \n";
    }
}