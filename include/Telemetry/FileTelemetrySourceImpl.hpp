#ifndef FILE_TELEMETRY_SOURCE_IMPL_HPP
#define FILE_TELEMETRY_SOURCE_IMPL_HPP

#include "ITelemetrySource.hpp"
#include "safeFile.hpp"
#include <string>

class FileTelemetrySourceImpl : public ITelemetrySource
{
private:
    safeFile File;

public:
    FileTelemetrySourceImpl(const std::string &path);

    // /*     // To Apply Rule of Zero u should let the compiler generate them implicitly

    //     // Default Constructor
    //     FileTelemetrySourceImpl() = delete;

    //     // Copy Constructor
    //     FileTelemetrySourceImpl(const FileTelemetrySourceImpl &obj) = delete;

    //     // Copy Assignment Operator
    //     FileTelemetrySourceImpl &operator=(const FileTelemetrySourceImpl &obj) = delete;

    //     // Move Constructor
    //     FileTelemetrySourceImpl(FileTelemetrySourceImpl &&obj) = default;

    //     // Move Assignment Operator
    //     FileTelemetrySourceImpl &operator=(FileTelemetrySourceImpl &&obj) = default;

    //     // Destructor
    //     ~FileTelemetrySourceImpl() = default;
    // */
    bool openSource() override;

    bool readSource(std::string &out) override;
};

#endif // FILE_TELEMETRY_SOURCE_IMPL_HPP