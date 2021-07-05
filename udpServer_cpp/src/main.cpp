#include <fstream>
#include <iostream>
#include <memory>
#include <exception>

#include "CsvLogger.hpp"
#include "DscInterpreter.hpp"
#include "UdpListener.hpp"

const std::string IP = "127.0.0.1";
constexpr uint16_t PORT = 4000;

int main(int argc, char* argv[])
{
    try
    {
        auto myLogger = std::make_unique<logger::CsvLogger>();
        auto myListener = std::make_unique<interpreter::DscInterpreter>(std::move(myLogger));

        udp_listener::UdpListener udpListenObj(IP, PORT, std::move(myListener));
        udpListenObj.receiveFrames();
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
