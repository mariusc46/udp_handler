#include "../src/CsvLogger.hpp"

class LoggerMock : public udp_listener::CsvLogger
{
    MOCK_METHOD(void, LogError, (), (override));
    MOCK_METHOD(void, LogMessage, (uint32_t mileage, float speed), (override));
};
