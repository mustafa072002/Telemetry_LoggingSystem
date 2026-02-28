#ifndef SAFE_SOCKET_HPP
#define SAFE_SOCKET_HPP


#include <string>


/**
 * @class safeSocket
 * @brief RAII-compliant wrapper for Unix Domain Socket operations.
 *
 * This class manages a Unix domain socket, ensuring safe acquisition and release of socket resources.
 * Only move semantics are allowed; copy semantics are deleted to prevent resource duplication.
 */
class safeSocket
{
private:
    int32_t sockFd;      /**< Socket file descriptor. */
    std::string path;    /**< Path to the Unix domain socket. */
    bool connected;      /**< Connection status. */
public:
    /**
     * @brief Deleted default constructor. Prevents socket-less objects.
     */
    safeSocket() = delete;

    /**
     * @brief Creates a Unix domain socket and stores the path.
     * @param path Path to the socket file.
     */
    safeSocket(const std::string& path);

    /**
     * @brief Deleted copy constructor.
     */
    safeSocket(const safeSocket& obj) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    safeSocket& operator=(const safeSocket& obj) = delete;

    /**
     * @brief Move constructor. Transfers ownership of socket descriptor.
     * @param obj Rvalue reference to another safeSocket.
     */
    safeSocket(safeSocket && obj) noexcept;

    /**
     * @brief Move assignment operator. Transfers ownership of socket descriptor.
     * @param obj Rvalue reference to another safeSocket.
     * @return Reference to this object.
     */
    safeSocket& operator=(safeSocket&& obj) noexcept;

    /**
     * @brief Destructor. Closes the socket if open.
     */
    ~safeSocket();

    /**
     * @brief Connects to the stored socket path.
     * @return True if successful, false otherwise.
     */
    bool connect();

    /**
     * @brief Connects to a specified socket path.
     * @param path Path to the socket file.
     * @return True if successful, false otherwise.
     */
    bool connect(const std::string& path);

    /**
     * @brief Sends data through the socket.
     * @param data String data to send.
     * @return True if successful, false otherwise.
     */
    bool sendData(const std::string& data);

    /**
     * @brief Receives data from the socket.
     * @param buffer Output string buffer.
     * @param size Number of bytes to receive.
     * @return True if successful, false otherwise.
     */
    bool receiveData(std::string &buffer, int32_t size);

    /**
     * @brief Disconnects and closes the socket.
     * @return True if successful, false otherwise.
     */
    bool disconnect();

    /**
     * @brief Checks if the socket is open.
     * @return True if open, false otherwise.
     */
    bool isOpen() const;

    /**
     * @brief Checks if the socket is connected.
     * @return True if connected, false otherwise.
     */
    bool isConnected() const;
};

#endif