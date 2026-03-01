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
    FileTelemetrySourceImpl() = delete;

    FileTelemetrySourceImpl(const std::string& path);

    FileTelemetrySourceImpl(const FileTelemetrySourceImpl &obj) = default;

    FileTelemetrySourceImpl &operator=(const FileTelemetrySourceImpl &obj) = default;

    FileTelemetrySourceImpl(FileTelemetrySourceImpl &&obj) = default;

    FileTelemetrySourceImpl &operator=(FileTelemetrySourceImpl &&obj) = default;

    bool openSource() override;

    bool readSource(std::string &out) override;
};

#endif // FILE_TELEMETRY_SOURCE_IMPL_HPP