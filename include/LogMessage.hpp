#ifndef LOG_MESSAGE_HEADER_HPP
#define LOG_MESSAGE_HEADER_HPP

#include <iostream>
#include <chrono>

class LogMessage
{
private:
    /* Private Attributes */
    std::string appName;
    std::string context;
    std::chrono::_V2::system_clock::time_point timeStamp;
    std::string severity;
    std::string payLoad;
    std::string fullMsg;

    /* Private Methods */
    std::string& fullMsgFiller();

protected:
public:
    /* Default Constructor */
    LogMessage();

    /* Parametrized Constructor */
    LogMessage(std::string appName , std::string context , std::string severity ,std::string payLoad);

    /* Apply Rule Of Five */

    // 1- Copy Constructor
    LogMessage(const LogMessage& obj) = default;

    // 2- Move Constructor
    LogMessage(LogMessage &&obj) = default;

    // 3- Copy Assignment Operator
    LogMessage& operator=(const LogMessage& obj) = default;

    // 4- Move Assignment Operator
    LogMessage& operator=(LogMessage&& obj) = default;
    /* 5- Destructor */
    ~LogMessage() = default;

    
    void fillMessage(std::string appName , std::string context , std::string severity ,std::string payLoad);
    std::string getMessage() const;
    
    /* Operator << Overloading */
    friend std::ostream& operator<<(std::ostream& os ,const LogMessage& msg);
};


#endif