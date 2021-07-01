#include <fstream>
#include <iomanip>
#include <iostream>

#include "CsvLogger.hpp"

namespace udp_listener 
{
    CsvLogger::CsvLogger()
    {
        std::string my_file_path = "../output/log.csv";
        m_myfile.open(my_file_path, std::fstream::trunc);
    }

    void CsvLogger::LogMessage(int64_t timestamp, uint32_t mileage, float speed)
    {
        m_myfile << timestamp << ", " << mileage << ", " << std::setprecision(1) << std::fixed << speed << std::endl;
    }

    void CsvLogger::LogError()
    {
        std::cerr << "CRC error, frame discarded \n";
    }
}
