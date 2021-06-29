#include "../libs/Network.h"
#include "MyListener.hpp"

namespace udp_listener
{
    class MyServerClass
    {
    public:
        void initServer(const std::string ip, const int port);
        void receiveFrames();

        udp_listener::MyListener myListenObj;
        udp_client_server::udp_server *myUdpServer;
    };
}
