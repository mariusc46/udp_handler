#include "../src/Logger.hpp"

class LoggerMock: public logger::Logger
{
public:
    MOCK_METHOD(void, LogError, (), (override));
    MOCK_METHOD(void, LogMessage, (uint32_t mileage, float speed), (override));
};
