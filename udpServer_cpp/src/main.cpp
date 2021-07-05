#include <fstream>
#include <iostream>
#include <memory>
#include <exception>

#include "CsvLogger.hpp"
#include "DscListener.hpp"
#include "UdpServer.hpp"

const std::string IP = "127.0.0.1";
constexpr uint16_t PORT = 4000;

int main(int argc, char* argv[])
{
    try
    {
        auto myLogger = std::make_unique<logger::CsvLogger>();
        auto myListener = std::make_unique<interpreter::DscListener>(std::move(myLogger));

        udp_listener::UdpServerClass udpServerObj(IP, PORT, std::move(myListener));
        udpServerObj.receiveFrames();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception occured. Exception nr. " << e.what() << "\n";
    }
    catch (...)
    {
        std::cout << "Unknown exception \n";
    }

    return 0;
}
