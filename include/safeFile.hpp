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



class safeFile
{
private:
    int32_t file;

public:
    // Delete Default Constructor (no Path Given)
    safeFile() = delete;

    // Parametrized Constructor for File Path
    safeFile(const std::string path);

    // Delete Copy Semantics
    safeFile(const safeFile &obj) = delete;

    safeFile &operator=(const safeFile &obj) = delete;

    // Move Semantics
    safeFile(safeFile &&obj) noexcept;

    safeFile &operator=(safeFile &&obj) noexcept;

    ~safeFile();

    // safeFile methods
    bool open(const std::string path);
    bool close();
    bool write(const std::string data);
    bool read(std::string &buffer, int32_t size);
    bool isOpen() const;
    bool isClosed() const;
};

#endif