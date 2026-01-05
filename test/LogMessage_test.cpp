#include <gtest/gtest.h>
#include <LogMessage.hpp>
#include <thread>
#include <chrono>
#include <algorithm>

/* Tested using AI :D */


// ==================== Default Constructor Tests ====================

TEST(LogMessageTest, DefaultConstructor_SetsDefaultValues)
{
    LogMessage msg;
    std::string fullMsg = msg.getMessage();
    std::cout << fullMsg <<std::endl;

    EXPECT_NE(fullMsg.find("NO_NAME"), std::string::npos);
    EXPECT_NE(fullMsg.find("INFO"), std::string::npos);
    EXPECT_NE(fullMsg.find("NAN"), std::string::npos);
}

TEST(LogMessageTest, DefaultConstructor_ReturnsNonEmptyMessage)
{
    LogMessage msg;
    EXPECT_FALSE(msg.getMessage().empty());
}

TEST(LogMessageTest, DefaultConstructor_MessageHasCorrectFormat)
{
    LogMessage msg;
    std::string fullMsg = msg.getMessage();

    // Count brackets - should have 5 pairs for [appName] [timestamp] [context] [severity] [payLoad]
    int openBrackets = std::count(fullMsg.begin(), fullMsg.end(), '[');
    int closeBrackets = std::count(fullMsg.begin(), fullMsg.end(), ']');

    EXPECT_EQ(openBrackets, 5);
    EXPECT_EQ(closeBrackets, 5);
}

// ==================== Parameterized Constructor Tests ====================

TEST(LogMessageTest, ParameterizedConstructor_SetsAllFields)
{
    LogMessage msg("MyApp", "NetworkModule", "ERROR", "Connection failed");
    std::string fullMsg = msg.getMessage();
    std::cout << fullMsg <<std::endl;
    EXPECT_NE(fullMsg.find("MyApp"), std::string::npos);
    EXPECT_NE(fullMsg.find("NetworkModule"), std::string::npos);
    EXPECT_NE(fullMsg.find("ERROR"), std::string::npos);
    EXPECT_NE(fullMsg.find("Connection failed"), std::string::npos);
}

TEST(LogMessageTest, ParameterizedConstructor_VariousSeverityLevels)
{
    std::vector<std::string> severities = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};

    for (const auto& severity : severities)
    {
        LogMessage msg("App", "Context", severity, "Payload");
        EXPECT_NE(msg.getMessage().find(severity), std::string::npos);
    }
}

TEST(LogMessageTest, ParameterizedConstructor_WithEmptyStrings)
{
    LogMessage msg("", "", "", "");
    std::string fullMsg = msg.getMessage();

    // Should still have the bracket structure
    EXPECT_NE(fullMsg.find("[]"), std::string::npos);
}

TEST(LogMessageTest, ParameterizedConstructor_WithSpecialCharacters)
{
    LogMessage msg("App@123", "Context#456", "INFO", "Payload with !@#$%^&*()");
    std::string fullMsg = msg.getMessage();

    EXPECT_NE(fullMsg.find("App@123"), std::string::npos);
    EXPECT_NE(fullMsg.find("Context#456"), std::string::npos);
    EXPECT_NE(fullMsg.find("!@#$%^&*()"), std::string::npos);
}

// ==================== fillMessage() Method Tests ====================

TEST(LogMessageTest, FillMessage_UpdatesAllFields)
{
    LogMessage msg;
    msg.fillMessage("UpdatedApp", "UpdatedContext", "WARNING", "Updated payload");
    std::string fullMsg = msg.getMessage();

    EXPECT_NE(fullMsg.find("UpdatedApp"), std::string::npos);
    EXPECT_NE(fullMsg.find("UpdatedContext"), std::string::npos);
    EXPECT_NE(fullMsg.find("WARNING"), std::string::npos);
    EXPECT_NE(fullMsg.find("Updated payload"), std::string::npos);
}

TEST(LogMessageTest, FillMessage_OverwritesPreviousValues)
{
    LogMessage msg("OldApp", "OldContext", "INFO", "Old payload");
    std::string oldMsg = msg.getMessage();
    std::cout << "oldMsg: " << oldMsg << std::endl;
    msg.fillMessage("NewApp", "NewContext", "ERROR", "New payload");
    std::string fullMsg = msg.getMessage();
    std::cout << "fullMsg: " << fullMsg << std::endl;

    // Old values should not be present
    EXPECT_EQ(fullMsg.find("OldApp"), std::string::npos);
    EXPECT_EQ(fullMsg.find("OldContext"), std::string::npos);
    EXPECT_EQ(fullMsg.find("Old payload"), std::string::npos);

    // New values should be present
    EXPECT_NE(fullMsg.find("NewApp"), std::string::npos);
    EXPECT_NE(fullMsg.find("NewContext"), std::string::npos);
    EXPECT_NE(fullMsg.find("ERROR"), std::string::npos);
    EXPECT_NE(fullMsg.find("New payload"), std::string::npos);
}

// ==================== getMessage() Method Tests ====================

TEST(LogMessageTest, GetMessage_ReturnsConsistentValue)
{
    LogMessage msg("App", "Context", "INFO", "Payload");

    std::string msg1 = msg.getMessage();
    std::string msg2 = msg.getMessage();

    EXPECT_EQ(msg1, msg2);
}

TEST(LogMessageTest, GetMessage_ContainsAllComponents)
{
    LogMessage msg("TestApp", "TestContext", "DEBUG", "TestPayload");
    std::string fullMsg = msg.getMessage();

    EXPECT_NE(fullMsg.find("[TestApp]"), std::string::npos);
    EXPECT_NE(fullMsg.find("[TestContext]"), std::string::npos);
    EXPECT_NE(fullMsg.find("[DEBUG]"), std::string::npos);
    EXPECT_NE(fullMsg.find("[TestPayload]"), std::string::npos);
}

// ==================== Copy/Move Semantics Tests ====================

TEST(LogMessageTest, CopyConstructor_CreatesIndependentCopy)
{
    LogMessage original("App", "Context", "INFO", "Payload");
    LogMessage copy(original);

    EXPECT_EQ(original.getMessage(), copy.getMessage());
}

TEST(LogMessageTest, CopyAssignment_CreatesIndependentCopy)
{
    LogMessage original("App", "Context", "INFO", "Payload");
    LogMessage copy;
    copy = original;

    EXPECT_EQ(original.getMessage(), copy.getMessage());
}

TEST(LogMessageTest, MoveConstructor_TransfersOwnership)
{
    LogMessage original("App", "Context", "INFO", "Payload");
    std::string originalMsg = original.getMessage();

    LogMessage moved(std::move(original));

    EXPECT_EQ(moved.getMessage(), originalMsg);
}

TEST(LogMessageTest, MoveAssignment_TransfersOwnership)
{
    LogMessage original("App", "Context", "INFO", "Payload");
    std::string originalMsg = original.getMessage();

    LogMessage moved;
    moved = std::move(original);

    EXPECT_EQ(moved.getMessage(), originalMsg);
}

// ==================== Edge Cases ====================

TEST(LogMessageTest, EdgeCase_VeryLongStrings)
{
    std::string longString(1000, 'A');
    LogMessage msg(longString, longString, "INFO", longString);
    std::string fullMsg = msg.getMessage();

    EXPECT_NE(fullMsg.find(longString), std::string::npos);
}

TEST(LogMessageTest, EdgeCase_WhitespaceHandling)
{
    LogMessage msg("  App  ", "  Context  ", "INFO", "  Payload  ");
    std::string fullMsg = msg.getMessage();

    EXPECT_NE(fullMsg.find("  App  "), std::string::npos);
    EXPECT_NE(fullMsg.find("  Context  "), std::string::npos);
    EXPECT_NE(fullMsg.find("  Payload  "), std::string::npos);
}

TEST(LogMessageTest, EdgeCase_NewlineInPayload)
{
    LogMessage msg("App", "Context", "INFO", "Line1\nLine2");
    std::string fullMsg = msg.getMessage();

    EXPECT_NE(fullMsg.find("Line1\nLine2"), std::string::npos);
}

// ==================== Timestamp Tests ====================

TEST(LogMessageTest, Timestamp_IncludedInMessage)
{
    LogMessage msg("App", "Context", "INFO", "Payload");
    std::string fullMsg = msg.getMessage();

    // Timestamp should contain year (2026 based on current date)
    // The format from ctime includes day, month, date, time, year
    EXPECT_NE(fullMsg.find("2026"), std::string::npos);
}

TEST(LogMessageTest, Timestamp_DifferentForDifferentMessages)
{
    LogMessage msg1("App", "Context", "INFO", "Payload");
    
    // Small delay to ensure different timestamp
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    LogMessage msg2("App", "Context", "INFO", "Payload");

    // Messages should be different due to timestamp
    EXPECT_NE(msg1.getMessage(), msg2.getMessage());
}

TEST(LogMessageTest, Timestamp_UpdatesOnFillMessage)
{
    LogMessage msg("App", "Context", "INFO", "Payload");
    std::string firstMsg = msg.getMessage();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    msg.fillMessage("App", "Context", "INFO", "Payload");
    std::string secondMsg = msg.getMessage();

    // Timestamp should have changed
    EXPECT_NE(firstMsg, secondMsg);
}


TEST(LogMessageTest , OUT_OPERATOR_OVERLOAD)
{
    LogMessage msg("App", "Context", "INFO", "Payload");
    std::cout << msg << std::endl;
    EXPECT_EQ(msg.getMessage() , (std::stringstream() << msg).str());
}