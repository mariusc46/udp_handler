#include <iostream>
#include <fstream>
#include <iomanip>

#include "MyLogger.hpp"

udp_listener::MyLogger::MyLogger()
{
    std::string my_file_path = "../output/log.csv";
    _myfile.open(my_file_path, std::fstream::trunc);
}

void udp_listener::MyLogger::LogMessage(int64_t timestamp, uint32_t mileage, float speed)
{
    _myfile << timestamp << ", " << mileage << ", " << std::setprecision(2) << std::fixed << speed << "\n";
    _myfile.flush();
    std::cout << "New log entry added!\n";
}

void udp_listener::MyLogger::LogError()
{
    std::cout << stderr << " CRC error, frame discarded \n";
}