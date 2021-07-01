#include "../libs/Network.h"
#include "MyListener.hpp"
#include <memory>

namespace udp_listener
{
    class MyServerClass
    {
    public:
        MyServerClass(const std::string ip, const int port);
        void receiveFrames();

        udp_listener::MyListener myListenObj;
        std::unique_ptr<udp_client_server::udp_server> myUdpServer;
    };
}
