#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>

#include "CsvLogger.hpp"

namespace udp_listener
{
    CsvLogger::CsvLogger()
    {
        std::string my_file_path = "../../output/log.csv";
        m_myfile.open(my_file_path, std::fstream::trunc);
    }

    int64_t CsvLogger::getUnixTimestamp() noexcept
    {
        int64_t microsecondsUTC =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return microsecondsUTC;
    }

    void CsvLogger::LogMessage(uint32_t mileage, float speed)
    {
        m_myfile << getUnixTimestamp() << ", " << mileage << ", " << std::setprecision(1) << std::fixed << speed << std::endl;
    }

    void CsvLogger::LogError() { std::cerr << "CRC error, frame discarded \n"; }
}
