#include "FileTelemetrySourceImpl.hpp"

FileTelemetrySourceImpl::FileTelemetrySourceImpl(const std::string& path) : File{safeFile(path)}
{

}

bool FileTelemetrySourceImpl::openSource()
{
    return File.open();
}

bool FileTelemetrySourceImpl::readSource(std::string& out)
{
   return File.read(out , 8192);
}