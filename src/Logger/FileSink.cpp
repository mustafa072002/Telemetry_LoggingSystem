#include <FileSink.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

FileSink::FileSink(const std::string &path)
{
    File = open(path.c_str(), O_RDWR | O_CREAT | O_APPEND, 0644);
}

FileSink::FileSink(FileSink &&obj) noexcept
{
    this->File = obj.File;
    obj.File = -1;
}

FileSink &FileSink::operator=(FileSink &&obj) noexcept
{
    if (this != &obj)
    {
        if (this->File != -1)
        {
            close(this->File);
        }
        this->File = obj.File;
        obj.File = -1;
    }
    return *this;
}

FileSink::~FileSink()
{
    if (File != -1)
    {
        close(File);
    }
}

void FileSink::write(const LogMessage &msg) const
{
    if (File == -1)
    {
        std::cerr << "File not open for writing" << std::endl;
        return;
    }
    std::cout << "Writing to File: " << msg.getMessage() << std::endl;
    std::string Log = msg.getMessage() + "\n";
    ::write(File, Log.c_str(), Log.size());
}