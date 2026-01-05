#include <ConsoleSink.hpp>
#include <iostream>

void ConsoleSink::write(const LogMessage& msg) const
{
    std::cout << msg <<std::endl;
}
