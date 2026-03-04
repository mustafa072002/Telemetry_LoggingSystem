#include "SocketTelemetrySourceImpl.hpp"
#include "safeSocket.hpp"


SocketTelemetrySourceImpl::SocketTelemetrySourceImpl(const std::string& path) : Socket{safeSocket(path)}
{

}


bool SocketTelemetrySourceImpl::openSource()
{
    return Socket.connect();
}

bool SocketTelemetrySourceImpl::readSource(std::string& out)
{
    return Socket.receiveData(out , 8192);
}