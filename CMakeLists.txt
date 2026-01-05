cmake_minimum_required(VERSION 3.14)
project(Telemetry_LoggingSystem C CXX)

find_package(GTest)
find_package(Threads)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(${PROJECT_NAME} test/LogMessage_test.cpp)

target_sources(${PROJECT_NAME} PRIVATE src/LogMessage.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest
    GTest::gtest_main
    Threads::Threads
)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})