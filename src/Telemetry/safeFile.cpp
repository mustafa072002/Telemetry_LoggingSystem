#include "safeFile.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// Parametrized Constructor
safeFile::safeFile(const std::string path)
{
    file = ::open(path.c_str(), O_RDWR | O_CREAT | O_APPEND, 0644);
}

// Move Constructor
safeFile::safeFile(safeFile &&obj) noexcept
{
    this->file = obj.file;
    obj.file = -1;
}

// Move Assignment operator
safeFile &safeFile::operator=(safeFile &&obj) noexcept
{
    if (this != &obj)
    {
        if (this->file != -1)
        {
            ::close(this->file);
        }
        this->file = obj.file;
        obj.file = -1;
    }
    return *this;
}

// Destructor
safeFile::~safeFile()
{
    if (file != -1)
    {
        ::close(file);
    }
}

// File Methods
bool safeFile::open(const std::string path)
{
    if (file != -1)
    {
        ::close(file);
    }
    int32_t state = ::open(path.c_str(), O_RDWR | O_CREAT | O_APPEND, 0644);
    if (state == -1)
    {
        return false;
    }
    else
    {
        file = state;
        return true;
    }
}

bool safeFile::close()
{   
    if (file == -1)
    {
        // File is already closed
        return false;
    }
    int32_t state = ::close(file);
    if (state == -1)
    {
        return false;
    }
    else
    {
        file = -1;
        return true;
    }
}

bool safeFile::write(const std::string data)
{
    if (file == -1 || data.empty())
    {
        return false;
    }

    int32_t bytes_written = ::write(file, data.c_str(), data.length());
    if (bytes_written == -1)
    {
        return false;
    }
    return true;
}

bool safeFile::read(std::string &buffer, int32_t size)
{
    if (file == -1 || size <= 0)
    {
        return false;
    }

    char *temp_buffer = new char[size];
    int32_t bytes_read = ::read(file, temp_buffer, size);

    if (bytes_read == -1)
    {
        delete[] temp_buffer;
        return false;
    }

    buffer.assign(temp_buffer, bytes_read);
    delete[] temp_buffer;
    return true;
}

bool safeFile::isOpen() const
{
    return (file != -1);
}

bool safeFile::isClosed() const
{
    return (file == -1);
}