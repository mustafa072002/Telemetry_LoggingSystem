#ifndef FILE_SINK_HEADER_HPP
#define FILE_SINK_HEADER_HPP

#include <ILogSink.hpp>
#include <LogMessage.hpp>

class FileSink : public ILogSink
{

private:
    int File;
public:

    /* Constructors */

    FileSink() = delete;

    /* Parametrized Constructor for File Path*/
    FileSink(const std::string& path);

    /* Delete Copy Constructor and Copy Assignment Operator as each File Can be Accessed By one Object */
    FileSink(const FileSink& obj) = delete;

    FileSink& operator=(const FileSink& obj) = delete;

    /* Move Constructor and Move Assignment Operator */
    FileSink(FileSink&& obj) noexcept;

    FileSink& operator=(FileSink&& obj) noexcept;


    ~FileSink();

    /* Overriding write Function */
    void write(const LogMessage& msg) const override; 
};

#endif