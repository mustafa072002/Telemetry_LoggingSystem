#include <LogMessage.hpp>
#include <ctime>
#include <chrono>

/* Private Helper Function For Updating fullMsg */
std::string &LogMessage::fullMsgFiller()
{
    std::time_t t = std::chrono::system_clock::to_time_t(this->timeStamp);

    std::string timeStr = std::ctime(&t);  // returns a string ending with '\n'
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();  // remove the trailing newline
    }

    fullMsg = "[" + this->appName + "] [" + timeStr + "] [" + this->context + "] [" + this->severity + "] [" + this->payLoad + "]";
    return fullMsg;
}


// Default Constructor
LogMessage::LogMessage() : appName("NO_NAME"), context("NO_NAME"), timeStamp(std::chrono::system_clock::now()), severity("INFO"), payLoad("NAN")
{
    fullMsg = fullMsgFiller();
}

// Parametrized Constructor
LogMessage::LogMessage(std::string appName, std::string context, std::string severity, std::string payLoad) : appName(appName), context(context), severity(severity),
                                                                                                              payLoad(payLoad), timeStamp(std::chrono::system_clock::now())
{
    fullMsg = fullMsgFiller();
}

// Method To Re-Fill The Message Content
void LogMessage::fillMessage(std::string appName, std::string context, std::string severity, std::string payLoad)
{
    this->appName = appName;
    this->context = context;
    this->severity = severity;
    this->payLoad = payLoad;
    this->timeStamp = std::chrono::system_clock::now();
    fullMsg = fullMsgFiller();
}

// Getter For Full Message
std::string LogMessage::getMessage() const
{
    return fullMsg;
}