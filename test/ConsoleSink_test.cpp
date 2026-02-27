#include "gtest/gtest.h"
#include "ConsoleSink.hpp"
#include "LogMessage.hpp"
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


class ConsoleSinkTest : public ::testing::Test
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


TEST_F(ConsoleSinkTest,CreateConsoleInstance)
{    
    ConsoleSink& sink1 = ConsoleSink::instance();
    sink1.write(msg);
    EXPECT_TRUE(true); // Just to Avoid Warning of No Expect in Test
}

TEST_F(ConsoleSinkTest , CreateILogSinkReference)
{
    ILogSink& sink1 = ConsoleSink::instance();
    msg.fillMessage("MyApp", "HardwareModule", "INFO", "Hardware initialized successfully");
    sink1.write(msg);
    EXPECT_TRUE(true); // Just to Avoid Warning of No Expect in Test
}

TEST_F(ConsoleSinkTest,SingletonProperty)
{
    ConsoleSink& sink1 = ConsoleSink::instance();
    ConsoleSink& sink2 = ConsoleSink::instance();

    EXPECT_EQ(&sink1, &sink2); // Both references should point to the same instance
}

TEST_F(ConsoleSinkTest,ThreadSafety)
{
    std::thread t1([&](){
        ILogSink& sink1 = ConsoleSink::instance();
        sink1.write(msg);
        std::cout << "Sink1 Wrote\n";
    });
    
    std::thread t2([&](){
        msg.fillMessage("MyApp", "DatabaseModule", "WARNING", "Query took too long");
        ILogSink& sink2 = ConsoleSink::instance();
        sink2.write(msg);
        std::cout << "Sink2 Wrote\n";
    });
    
    t1.join();
    t2.join();

    EXPECT_TRUE(true); // Just to Avoid Warning of No Expect in Test
}