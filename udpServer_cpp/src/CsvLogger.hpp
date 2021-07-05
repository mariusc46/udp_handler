#pragma once
#include "Logger.hpp"
#include <fstream>

namespace udp_listener
{
    class CsvLogger : public Logger
    {
    public:
        CsvLogger();
        int64_t getUnixTimestamp() noexcept;
        void LogMessage(uint32_t mileage, float speed) override;
        void LogError() override;

    private:
        std::ofstream m_myfile;
    };
}
