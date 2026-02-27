# Telemetry_LoggingSystem
This project is a scalable, multi-threaded logging system written in C++; designed with best architectural and implementation practices in mind, while utilizing both the power Modern C++ provides in addition to industry-standard libraries and tools.

## Components
- **Logger Manager**: A singleton class that manages multiple loggers, each identified by a unique name. It provides methods to create, retrieve, and configure loggers.
- **Log Message**: A structure that encapsulates log message details, including timestamp, log level, message content, and logger name.
- **Log Sink Interfaces**: Abstract interfaces for different log sinks (console, file) that define methods for writing log messages.
- **Console Logger**: A logger that outputs log messages to the console (standard output).
- **File Logger**: A logger that writes log messages to a specified file, with support for log rotation based on file size.
