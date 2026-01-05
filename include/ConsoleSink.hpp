#ifndef CONSOLE_SINK_HEADER_HPP
#define CONSOLE_SINK_HEADER_HPP

#include <ILogSink.hpp>
#include <LogMessage.hpp>

class ConsoleSink : public ILogSink
{
public:
    /* Only One Object Cans Access Console */
    /* Access point to the single instance */
    static ConsoleSink& instance();

    /* Delete Copy Constructor and Copy Assignment operator (Only one Console Object) */
    ConsoleSink(const ConsoleSink &obj) = delete;

    ConsoleSink &operator=(const ConsoleSink &obj) = delete;

    /* Delete Move Constructor and Move Assignment Operator */
    ConsoleSink(ConsoleSink &&obj) = delete;

    ConsoleSink &operator=(ConsoleSink &&obj) = delete;

    /* Overriding write Function */
    void write(const LogMessage &msg) const override;

private:
    /* Constructors Private */
    /* Singleton */
    ConsoleSink() = default;

    ~ConsoleSink() = default;
};

#endif