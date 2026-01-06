#include "LogManager.hpp"
#include <algorithm>


LogManager::LogManager(uint32_t BufferSize) : BufferSize{BufferSize}
{

}

void LogManager::addSink(ILogSink &sink)
{
    systemSinkers.push_back(&sink);
}

void LogManager::removeSink(ILogSink &sink)
{
    systemSinkers.erase(std::remove(systemSinkers.begin(), systemSinkers.end(), &sink), systemSinkers.end());
}

void LogManager::addMsg(const LogMessage& msg)
{
    if (currentSize < BufferSize)
    {
        // buffer not full → append at the end
        msgBuffer[(head + currentSize) % BufferSize] = msg;
        ++currentSize;
    }
    else
    {
        // buffer full → overwrite oldest
        msgBuffer[head] = msg;
        head = (head + 1) % BufferSize; // move oldest forward
    }
}

void LogManager::write(ILogSink &sink)
{
    for (std::size_t i = 0; i < currentSize; ++i)
    {
        std::size_t index = (head + i) % BufferSize;
        sink.write(msgBuffer[index]);
    }
}

void LogManager::writeToAll()
{
    for (auto sink : systemSinkers)
    {
        write(*sink);
    }
}
