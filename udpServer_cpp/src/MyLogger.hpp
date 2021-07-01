#include "Logger.hpp"
#include <fstream>

namespace udp_listener
{
    class MyLogger : public udp_listener::Logger
    {
    public:
        MyLogger();
        virtual void LogMessage(int64_t timestamp, uint32_t mileage, float speed);
        virtual void LogError();

    private:
        std::ofstream _myfile;
    };
}
