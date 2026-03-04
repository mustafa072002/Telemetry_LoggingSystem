#ifndef SOCKET_TELEMETRY_SOURCE_IMPL_HPP
#define SOCKET_TELEMETRY_SOURCE_IMPL_HPP

#include "ITelemetrySource.hpp"
#include "safeSocket.hpp"
#include <string>

class SocketTelemetrySourceImpl : public ITelemetrySource
{
private:
    safeSocket Socket;

public:
    // Parameterized Constructor
    SocketTelemetrySourceImpl(const std::string &path);

    // To Apply Rule of Zero you should let the compiler generate them implicitly
    /*

        // Default Constructor
        SocketTelemetrySourceImpl() = delete;

        //   Copy Constructor
        SocketTelemetrySourceImpl(const SocketTelemetrySourceImpl &obj) = delete;

        // Copy Assignment Operator
        SocketTelemetrySourceImpl &operator=(const SocketTelemetrySourceImpl &obj) = delete;

        // Move Constructor
        SocketTelemetrySourceImpl(SocketTelemetrySourceImpl &&obj) = default;

        // Move Assignment Operator
        SocketTelemetrySourceImpl &operator=(SocketTelemetrySourceImpl &&obj) = default;

        // Destructor
        ~SocketTelemetrySourceImpl() = default;
    */

    // Interface Methods
    bool openSource() override;

    bool readSource(std::string &out) override;

};

#endif // SOCKET_TELEMETRY_SOURCE_IMPL_HPP