cmake_minimum_required(VERSION 3.14)
project(Telemetry_LoggingSystem C CXX)
set(CMAKE_CXX_FLAGS "-g")

find_package(GTest REQUIRED)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable CTest
enable_testing()

# Set Source Files

# -------- For LogMessage Tests --------
# set(SRC_FILE src/LogMessage.cpp)
# set(SRC_TEST test/LogMessage_test.cpp)
# set(TEST_NAME LogMessageTest)


# -------- For ConsoleSink Tests --------
# set(SRC_FILE src/ConsoleSink.cpp src/LogMessage.cpp)
# set(SRC_TEST test/ConsoleSink_test.cpp)
# set(TEST_NAME ConsoleSinkTest)


# -------- For FileSink Tests --------
# set(SRC_FILE src/FileSink.cpp src/LogMessage.cpp)
# set(SRC_TEST test/FileSink_test.cpp)
# set(TEST_NAME FileSinkTest)


# -------- For FileTelemetrySourceImpl Tests --------
set(SRC_FILE src/safeFile.cpp src/Telemetry/FileTelemetrySourceImpl.cpp)
set(SRC_TEST test/FileTelemetrySourceImpl_test.cpp)
set(TEST_NAME FileTelemetrySourceImplTest)




# Create Executable for Tests
add_executable(${TEST_NAME} ${SRC_FILE} ${SRC_TEST})

target_include_directories(${TEST_NAME} PUBLIC include include/Logger include/Telemetry)

target_link_libraries(${TEST_NAME}
    GTest::GTest 
    GTest::Main
    )

include(GoogleTest)
# Automatically discover and add tests
gtest_discover_tests(${TEST_NAME})