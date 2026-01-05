#ifndef FILE_SINK_HEADER_HPP
#define FILE_SINK_HEADER_HPP

#include <ILogSink.hpp>
#include <LogMessage.hpp>

class FileSink : public ILogSink
{

private:
    int fd;
public:

    /* Constructors */

    FileSink() = delete;

    /* Parametrized Constructor for File Path*/
    FileSink(std::string& path);

    /* Delete Copy Constructor and Copy Assignment Operator as File Can be Accessed By one Object */
    FileSink(const FileSink& obj) = delete;

    FileSink& operator=(const FileSink& obj) = delete;

    /* Default Move Constructor and Move Assignment Operator */
    FileSink(FileSink&& obj);

    FileSink& operator=(FileSink&& obj);


    ~FileSink();

    /* Overriding write Function */
    void write(const LogMessage& msg) const override; 
};

#endif