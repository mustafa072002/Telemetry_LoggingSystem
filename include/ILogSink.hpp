#ifndef INTERFACE_LOG_SINK_HPP
#define INTERFACE_LOG_SINK_HPP

#include "LogMessage.hpp"

class ILogSink
{
public:
    virtual void write(const LogMessage& msg) const = 0; 

    virtual ~ILogSink() = default;
};

#endif