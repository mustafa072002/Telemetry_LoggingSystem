#include "gtest/gtest.h"
#include "LogMessage.hpp"
#include "FileSink.hpp"
#include "ILogSink.hpp"
#include <iostream>
#include <thread>


/* For Studying */
/**
 * TEST(TEST_SUIT_NAME, TEST_CASE_NAME)
 * {
 *      1) Arrange
 *          Setup environment like making object , setting Variables ....
 *      2) Act
 *          Call Function You Want To Test
 *      3) Expect
 *          Expect Result of the function with the Required Result
 * }  
*/


class FileSinkTest : public ::testing::Test
{
protected:
    LogMessage msg;
    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right before each test).
        msg = LogMessage("MyApp", "NetworkModule", "ERROR", "Connection failed");
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right before the destructor).
        std::cout << "Test Finished" << std::endl;
    }
};

TEST_F(FileSinkTest,LogMessageToFile)
{   
    FileSink fileSink("logTest.txt");
    fileSink.write(msg);
    std::cout << "Message Written to File" << std::endl;
    EXPECT_TRUE(true); // Just to Avoid Warning of No Expect in Test
}

TEST_F(FileSinkTest,CreateILogSinkReference)
{
    FileSink fileSink("logTest.txt");
    ILogSink& sink1 = fileSink;
    msg.fillMessage("MyApp", "HardwareModule", "INFO", "Hardware initialized successfully");
    sink1.write(msg);
    std::cout << "Message Written to File through ILogSink reference" << std::endl;
    EXPECT_TRUE(true); // Just to Avoid Warning of No Expect in Test
}