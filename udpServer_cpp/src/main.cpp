#include <fstream>
#include <iostream>
#include <memory>
#include <exception>

#include "CsvLogger.hpp"
#include "DscListener.hpp"
#include "MyServer.hpp"

const std::string IP = "127.0.0.1";
constexpr uint16_t PORT = 4000;

int main(int argc, char* argv[])
{
    try
    {
        using namespace udp_listener;

        auto myLogger = std::make_unique<CsvLogger>();
        // auto myListener = std::make_unique<DscListener>(std::move(myLogger));

        // MyServerClass myServerObj(IP, PORT, std::move(myListener));
        // myServerObj.receiveFrames();
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
