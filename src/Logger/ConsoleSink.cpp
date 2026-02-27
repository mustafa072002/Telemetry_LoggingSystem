#include <ConsoleSink.hpp>
#include <iostream>

void ConsoleSink::write(const LogMessage& msg) const
{
    std::cout << msg <<std::endl;
}


ConsoleSink& ConsoleSink::instance()
{
    static ConsoleSink instance;  // created once, thread-safe since C++11
    return instance;
}