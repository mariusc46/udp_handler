#include <iostream>
#include <fstream>

#include "MyServer.hpp"

const std::string IP = "127.0.0.1";
const int PORT = 4000;

int main(int argc, char *argv[])
{
    udp_listener::MyServerClass myServerObj;

    try
    {
        myServerObj.initServer(IP, PORT);
        myServerObj.receiveFrames();
    }
    catch (int e)
    {
        std::cout << "Exception occured. Exception nr. " << e << "\n";
    }

    return 0;
}
