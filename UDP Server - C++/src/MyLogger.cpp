#include <fstream>
#include <iomanip>
#include <iostream>

#include "MyLogger.hpp"

udp_listener::MyLogger::MyLogger()
{
    std::string my_file_path = "../output/log.csv";
    _myfile.open(my_file_path, std::fstream::trunc);
}

void udp_listener::MyLogger::LogMessage(int64_t timestamp, uint32_t mileage, float speed)
{
    _myfile << timestamp << ", " << mileage << ", " << std::setprecision(2) << std::fixed << speed << std::endl;
    std::cout << "New log entry added!\n";
}

void udp_listener::MyLogger::LogError()
{
    std::cerr << " CRC error, frame discarded";
}