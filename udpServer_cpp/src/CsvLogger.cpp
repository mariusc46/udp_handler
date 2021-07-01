#include <fstream>
#include <iomanip>
#include <iostream>

#include "CsvLogger.hpp"

udp_listener::CsvLogger::CsvLogger()
{
    std::string my_file_path = "../output/log.csv";
    _myfile.open(my_file_path, std::fstream::trunc);
}

void udp_listener::CsvLogger::LogMessage(int64_t timestamp, uint32_t mileage, float speed)
{
    _myfile << timestamp << ", " << mileage << ", " << std::setprecision(1) << std::fixed << speed << std::endl;
}

void udp_listener::CsvLogger::LogError()
{
    std::cerr << "CRC error, frame discarded \n";
}
