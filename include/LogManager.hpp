#ifndef LOG_MANAGER_HEADER_HPP
#define LOG_MANAGER_HEADER_HPP

#include "LogMessage.hpp"
#include "ILogSink.hpp"
#include "stdint.h"
#include <vector>

class LogManager
{
private:
    std::vector<LogMessage> msgBuffer;
    std::vector<ILogSink *> systemSinkers;

    std::size_t head = 0;        // index of oldest message
    std::size_t currentSize = 0; // number of valid messages
    std::size_t BufferSize = 50; // default buffer size

public:
    LogManager() = default;
    LogManager(uint32_t BufferSize);

    ~LogManager() = default;

    LogManager(const LogManager &obj) = delete;
    LogManager &operator=(const LogManager &obj) = delete;

    LogManager(LogManager &&obj) = default;
    LogManager &operator=(LogManager &&obj) = default;

    void addMsg(const LogMessage &msg);

    void addSink(ILogSink &sink);
    void removeSink(ILogSink &sink);

    void writeToAll();
    void write(ILogSink &sink);
};

#endif // LOG_MANAGER_HEADER_HPP