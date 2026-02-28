#ifndef SAFE_FILE_HPP
#define SAFE_FILE_HPP

#include <string>
/**
 * @file safeFile.hpp
 * @brief Safe file handling interface with RAII principles
 * @author Mustafa Mahgoub
 * @date 2026-02-27
 * 
 * @class safeFile
 * @brief Provides a safe interface for handling file operations
 * 
 * This class implements RAII principles to ensure proper resource management
 * of file operations. File resources are automatically released when the object
 * goes out of scope.
 * 
 * @details
 * Design Flow:
 * - Default constructor is deleted to prevent file-less objects
 * - Parametrized constructor opens file and stores file descriptor
 * - Copy semantics are deleted to prevent resource duplication
 * - Move semantics enable safe resource transfer
 * - Destructor ensures proper file resource cleanup
 * 
 * @note The class uses move semantics instead of copying to maintain
 * exclusive ownership of file resources.
 */




/**
 * @class safeFile
 * @brief RAII-compliant wrapper for POSIX file operations.
 *
 * This class manages a file descriptor, ensuring safe acquisition and release of file resources.
 * Only move semantics are allowed; copy semantics are deleted to prevent resource duplication.
 */
class safeFile
{
private:
    int32_t file; /**< POSIX file descriptor. */

public:
    /**
     * @brief Deleted default constructor. Prevents file-less objects.
     */
    safeFile() = delete;

    /**
     * @brief Opens a file and acquires its descriptor.
     * @param path Path to the file.
     */
    safeFile(const std::string& path);

    /**
     * @brief Deleted copy constructor.
     */
    safeFile(const safeFile &obj) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    safeFile &operator=(const safeFile &obj) = delete;

    /**
     * @brief Move constructor. Transfers ownership of file descriptor.
     * @param obj Rvalue reference to another safeFile.
     */
    safeFile(safeFile &&obj) noexcept;

    /**
     * @brief Move assignment operator. Transfers ownership of file descriptor.
     * @param obj Rvalue reference to another safeFile.
     * @return Reference to this object.
     */
    safeFile &operator=(safeFile &&obj) noexcept;

    /**
     * @brief Destructor. Closes the file if open.
     */
    ~safeFile();

    /**
     * @brief Opens a file, closing any previously opened file.
     * @param path Path to the file.
     * @return True if successful, false otherwise.
     */
    bool open(const std::string path);

    /**
     * @brief Closes the file if open.
     * @return True if successful, false otherwise.
     */
    bool close();

    /**
     * @brief Writes data to the file.
     * @param data String data to write.
     * @return True if successful, false otherwise.
     */
    bool write(const std::string data);

    /**
     * @brief Reads data from the file.
     * @param buffer Output string buffer.
     * @param size Number of bytes to read.
     * @return True if successful, false otherwise.
     */
    bool read(std::string &buffer, int32_t size) const;

    /**
     * @brief Checks if the file is open.
     * @return True if open, false otherwise.
     */
    bool isOpen() const;

    /**
     * @brief Checks if the file is closed.
     * @return True if closed, false otherwise.
     */
    bool isClosed() const;
};

#endif