#include <limits>
#include <bits/stdc++.h>

#include "../libs/CRC.h"
#include "DscInterpreter.hpp"
#include "Logger.hpp"


namespace interpreter
{
    constexpr uint32_t NO_MESSAGE_LOGGED = std::numeric_limits<uint32_t>::max();

    DscInterpreter::DscInterpreter(std::unique_ptr<logger::Logger> logger): m_previous_log_mileage(NO_MESSAGE_LOGGED), m_logger(std::move(logger))
    {
    }

    float DscInterpreter::convertSpeedToKmh(const float speed_ms) noexcept
    {
        constexpr float msToKmhMultiplier = 3.6f;
        return (speed_ms * msToKmhMultiplier * 10U) / 10.0f;
    }

    uint16_t DscInterpreter::getMessageId() noexcept
    {
        uint16_t id = (m_singleFrameBuffer[0] << 8U) | m_singleFrameBuffer[1];
        return id;
    };

    bool DscInterpreter::validateCrc() noexcept
    {
        uint8_t crc = m_singleFrameBuffer[9];
        uint8_t expected_crc = Crc_CalculateCRC8H2F(m_singleFrameBuffer.data(), 9U, 0xff, true);

        return crc == expected_crc;
    }

    uint32_t DscInterpreter::getMileage() noexcept
    {
        uint32_t mileage = (uint32_t(m_singleFrameBuffer[3]) << 16U) | (uint32_t(m_singleFrameBuffer[4]) << 8U) | uint32_t(m_singleFrameBuffer[5]);
        return mileage;
    }

    uint32_t DscInterpreter::getSpeed() noexcept
    {
        uint32_t speed = (uint32_t(m_singleFrameBuffer[6]) << 16U) | (uint32_t(m_singleFrameBuffer[7]) << 8U) | uint32_t(m_singleFrameBuffer[8]);
        return speed;
    }

    bool DscInterpreter::isTimeToLog(const uint32_t mileage) noexcept
    {
        constexpr int log_required_interval = 10U;

        if (m_previous_log_mileage == NO_MESSAGE_LOGGED || mileage == m_previous_log_mileage + log_required_interval)
        {
            m_previous_log_mileage = mileage;
            return true;
        }

        return false;
    }

    void DscInterpreter::handleIncomingBuffer(const std::span<uint8_t> buffer)
    {
        constexpr uint16_t DEFINED_NUMBER_OF_BYTES = 10U;
        constexpr uint16_t ONE_CAN_MESSAGE_SIZE = 10U;

        if (buffer.size() == ONE_CAN_MESSAGE_SIZE)
        {
            m_singleFrameBuffer = buffer;
            handleOneCanFrame();
        }
        else // split UDP frame in smaller CAN frames
        {
            for (uint16_t bytes_index = 0U; bytes_index < buffer.size(); bytes_index += DEFINED_NUMBER_OF_BYTES)
            {
                m_singleFrameBuffer = std::span<uint8_t>(buffer.data() + bytes_index, 10U);
                handleOneCanFrame();
            }
        }
    }

    void DscInterpreter::handleOneCanFrame()
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
                    m_logger->LogMessage(mileage, convertSpeedToKmh(speed_ms));
                }
            }
            else
            {
                m_logger->LogError();
            }
        }
    }

}
