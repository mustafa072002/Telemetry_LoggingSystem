#ifndef CONSOLE_SINK_HEADER_HPP
#define CONSOLE_SINK_HEADER_HPP

#include <ILogSink.hpp>
#include <LogMessage.hpp>

class ConsoleSink : public ILogSink
{
public:

    /* Constructors */

    ConsoleSink() = default;

    /* Delete Copy Constructor and Copy Assignment operator (Only one Console Object) */
    ConsoleSink(const ConsoleSink& obj) = delete;

    ConsoleSink& operator=(const ConsoleSink& obj) = delete;

    /* Default Move Constructor and Move Assignment Operator */
    ConsoleSink(ConsoleSink&& obj) = default;

    ConsoleSink& operator=(ConsoleSink&& obj) = default;


    ~ConsoleSink() = default;

    /* Overriding write Function */
    void write(const LogMessage& msg) const override; 
};

#endif