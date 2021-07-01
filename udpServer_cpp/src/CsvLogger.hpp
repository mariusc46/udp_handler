#pragma once
#include "Logger.hpp"
#include <fstream>

namespace udp_listener
{
    class CsvLogger : public Logger
    {
    public:
        CsvLogger();
        void LogMessage(int64_t timestamp, uint32_t mileage, float speed) override;
        void LogError() override;

    private:
        std::ofstream _myfile;
    };
}
