#include <iostream>
#include <fstream>

#include "MyServer.hpp"

const std::string IP = "127.0.0.1";
constexpr int PORT = 4000;

int main(int argc, char *argv[])
{
    try
    {
        udp_listener::MyServerClass myServerObj(IP, PORT);
        myServerObj.receiveFrames();
    }
    catch (int e)
    {
        std::cout << "Exception occured. Exception nr. " << e << "\n";
    }

    return 0;
}
