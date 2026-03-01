#include "safeFile.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief Constructs a safeFile and opens the specified file.
 * @param path Path to the file.
 */
safeFile::safeFile(const std::string& path) : path{path}
{
}

/**
 * @brief Move constructor. Transfers file descriptor ownership.
 * @param obj Rvalue reference to another safeFile.
 */
safeFile::safeFile(safeFile &&obj) noexcept
{   
    this->path = obj.path;
    this->file = obj.file;
    obj.file = -1;
}

/**
 * @brief Move assignment operator. Transfers file descriptor ownership.
 * @param obj Rvalue reference to another safeFile.
 * @return Reference to this object.
 */
safeFile &safeFile::operator=(safeFile &&obj) noexcept
{
    if (this != &obj)
    {
        if (this->file != -1)
        {
            ::close(this->file);
        }
        this->path = obj.path;
        this->file = obj.file;
        obj.file = -1;
    }
    return *this;
}

/**
 * @brief Destructor. Closes the file if open.
 */
safeFile::~safeFile()
{
    if (file != -1)
    {
        ::close(file);
    }
}

bool safeFile::open()
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

/**
 * @brief Opens a file, closing any previously opened file.
 * @param path Path to the file.
 * @return True if successful, false otherwise.
 */
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

/**
 * @brief Closes the file if open.
 * @return True if successful, false otherwise.
 */
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

/**
 * @brief Writes data to the file.
 * @param data String data to write.
 * @return True if successful, false otherwise.
 */
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

/**
 * @brief Reads data from the file.
 * @param buffer Output string buffer.
 * @param size Number of bytes to read.
 * @return True if successful, false otherwise.
 */
bool safeFile::read(std::string &buffer, int32_t size) const
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

/**
 * @brief Checks if the file is open.
 * @return True if open, false otherwise.
 */
bool safeFile::isOpen() const
{
    return (file != -1);
}

/**
 * @brief Checks if the file is closed.
 * @return True if closed, false otherwise.
 */
bool safeFile::isClosed() const
{
    return (file == -1);
}