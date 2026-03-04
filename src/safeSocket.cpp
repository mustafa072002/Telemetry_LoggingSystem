#include "safeSocket.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

/**
 * @brief Constructs a safeSocket and creates a Unix domain socket.
 * @param path Path to the socket file.
 */
safeSocket::safeSocket(const std::string &path) : path{path} , connected{false} , sockFd{-1}
{
    // 1. Create socket
    sockFd = ::socket(AF_UNIX, SOCK_STREAM, 0);
}

/**
 * @brief Move constructor. Transfers socket descriptor ownership.
 * @param obj Rvalue reference to another safeSocket.
 */
safeSocket::safeSocket(safeSocket &&obj) noexcept
{
    this->sockFd = obj.sockFd;
    this->path = std::move(obj.path);
    this->connected = obj.connected;

    obj.sockFd = -1;
    obj.path.clear();
    obj.connected = false;
}

/**
 * @brief Move assignment operator. Transfers socket descriptor ownership.
 * @param obj Rvalue reference to another safeSocket.
 * @return Reference to this object.
 */
safeSocket &safeSocket::operator=(safeSocket &&obj) noexcept
{
    if (this != &obj)
    {
        if (this->sockFd != -1)
        {
            ::close(sockFd);
        }
        this->sockFd = obj.sockFd;
        this->path = std::move(obj.path);
        this->connected = obj.connected;

        obj.sockFd = -1;
        obj.path.clear();
        obj.connected = false;
    }
    return *this;
}

/**
 * @brief Destructor. Disconnects and closes the socket if open.
 */
safeSocket::~safeSocket()
{
    disconnect();
}

// Socket Methods

/**
 * @brief Connects to the stored socket path.
 * @return True if successful, false otherwise.
 */
bool safeSocket::connect()
{
    if (path.empty())
    {
        return false;
    }
    else
    {
        if(connected)
        {
            return true;
        }
        // 1. Prepare Address
        sockaddr_un address = {};
        address.sun_family = AF_UNIX;
        std::strncpy(address.sun_path, path.c_str(), sizeof(address.sun_path) - 1);

        // 2. Connect
        int state = ::connect(sockFd, (sockaddr *)&address, sizeof(address));

        if (state == -1)
        {
            connected = false;
            return false;
        }
        else
        {
            connected = true;
            return true;
        }
    }
}

/**
 * @brief Connects to a specified socket path.
 * @param path Path to the socket file.
 * @return True if successful, false otherwise.
 */
bool safeSocket::connect(const std::string& path)
{
    if (path.empty())
    {
        return false;
    }
    else
    {
        this->path = path;
        // 1. Prepare Address
        sockaddr_un address = {};
        address.sun_family = AF_UNIX;
        std::strncpy(address.sun_path, path.c_str(), sizeof(address.sun_path) - 1);

        if (connected)
        {
            // Already connected to a socket, disconnect first
            disconnect();
            // Recreate socket since disconnect() closed the fd
            sockFd = ::socket(AF_UNIX, SOCK_STREAM, 0);
            if (sockFd == -1)
            {
                return false;
            }
        }
        // 2. Connect
        int state = ::connect(sockFd, (sockaddr *)&address, sizeof(address));

        if (state == -1)
        {
            connected = false;
            return false;
        }
        else
        {
            connected = true;
            return true;
        }
    }
}

/**
 * @brief Disconnects and closes the socket.
 * @return True if successful, false otherwise.
 */
bool safeSocket::disconnect()
{
    if (sockFd == -1)
    {
        return false;
    }
    int state = ::close(sockFd);
    if (state == -1)
    {
        connected = false;
        return false;
    }
    else
    {
        sockFd = -1;
        connected = false;
        return true;
    }
}

/**
 * @brief Sends data through the socket.
 * @param data String data to send.
 * @return True if successful, false otherwise.
 */
bool safeSocket::sendData(const std::string& data)
{
    if (data.empty() || !(isConnected()))
    {
        return false;
    }
    int32_t bytes_written = ::send(sockFd, data.c_str(), data.length(), 0);
    if (bytes_written == -1)
    {
        connected = false;
        return false;
    }
    return true;
}

/**
 * @brief Receives data from the socket.
 * @param buffer Output string buffer.
 * @param size Number of bytes to receive.
 * @return True if successful, false otherwise.
 */
bool safeSocket::receiveData(std::string &buffer, int32_t size)
{
    if (sockFd == -1 || size <= 0 || !(isConnected()))
    {
        return false;
    }

    std::string temp_buffer(size, '\0');
    int32_t bytes_read = ::recv(sockFd, &temp_buffer[0], size, 0);

    if (bytes_read == -1 || bytes_read == 0)
    {
        connected = false;
        return false;
    }

    temp_buffer.resize(bytes_read);
    buffer = std::move(temp_buffer);
    connected = true;
    return true;
}

/**
 * @brief Checks if the socket is open.
 * @return True if open, false otherwise.
 */
bool safeSocket::isOpen() const
{
    return (sockFd != -1);
}

/**
 * @brief Checks if the socket is connected.
 * @return True if connected, false otherwise.
 */
bool safeSocket::isConnected() const
{
    if (sockFd == -1)
    {
        return false;
    }
    else
    {
        return connected;
    }
}