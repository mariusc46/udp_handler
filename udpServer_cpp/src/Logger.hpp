namespace udp_listener
{
    class Logger
    {
    public:
        virtual void LogMessage(int64_t timestamp, uint32_t mileage, float speed) = 0;
        virtual void LogError() = 0;
    };
}
