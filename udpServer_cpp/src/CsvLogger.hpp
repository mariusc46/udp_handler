#pragma once
#include "Logger.hpp"
#include <fstream>

namespace logger
{
    class CsvLogger: public Logger
    {
    public:
        CsvLogger();
        static int64_t getUnixTimestamp() noexcept;
        void LogMessage(uint32_t mileage, float speed) override;
        void LogError() override;

    private:
        std::ofstream m_myfile;
    };
}
