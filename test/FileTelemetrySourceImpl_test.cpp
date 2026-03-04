#include <gtest/gtest.h>
#include <FileTelemetrySourceImpl.hpp>
#include <string>
#include <fstream>

// ==================== Construction Tests ====================

TEST(FileTelemetrySourceImplTest, ConstructWithValidPath)
{
    FileTelemetrySourceImpl source("/proc/stat");
    // Object should be constructable without throwing
    SUCCEED();
}

TEST(FileTelemetrySourceImplTest, ConstructWithInvalidPath)
{
    FileTelemetrySourceImpl source("/nonexistent/path/file.txt");
    // Construction should not throw, open should fail
    EXPECT_FALSE(source.openSource());
}

// ==================== Move Semantics Tests ====================

TEST(FileTelemetrySourceImplTest, MoveConstructor)
{
    FileTelemetrySourceImpl source("/proc/stat");
    ASSERT_TRUE(source.openSource());

    // Move construct a new source
    FileTelemetrySourceImpl movedSource(std::move(source));

    std::string data;
    EXPECT_TRUE(movedSource.readSource(data));
    EXPECT_FALSE(data.empty());
}

TEST(FileTelemetrySourceImplTest, MoveAssignment)
{
    FileTelemetrySourceImpl source("/proc/stat");
    ASSERT_TRUE(source.openSource());

    FileTelemetrySourceImpl target("/proc/meminfo");
    target = std::move(source);

    std::string data;
    EXPECT_TRUE(target.readSource(data));
    EXPECT_FALSE(data.empty());
}

// ==================== /proc/stat Tests ====================

TEST(FileTelemetrySourceImplTest, OpenProcStat)
{
    FileTelemetrySourceImpl source("/proc/stat");
    EXPECT_TRUE(source.openSource());
}

TEST(FileTelemetrySourceImplTest, ReadProcStat_ReturnsData)
{
    FileTelemetrySourceImpl source("/proc/stat");
    ASSERT_TRUE(source.openSource());

    std::string data;
    EXPECT_TRUE(source.readSource(data));
    EXPECT_FALSE(data.empty());
}

TEST(FileTelemetrySourceImplTest, ReadProcStat_ContainsCpuInfo)
{
    FileTelemetrySourceImpl source("/proc/stat");
    ASSERT_TRUE(source.openSource());

    std::string data;
    ASSERT_TRUE(source.readSource(data));

    // /proc/stat always starts with "cpu" line
    EXPECT_NE(data.find("cpu"), std::string::npos);
}

// ==================== /proc/meminfo Tests ====================

TEST(FileTelemetrySourceImplTest, OpenProcMeminfo)
{
    FileTelemetrySourceImpl source("/proc/meminfo");
    EXPECT_TRUE(source.openSource());
}

TEST(FileTelemetrySourceImplTest, ReadProcMeminfo_ReturnsData)
{
    FileTelemetrySourceImpl source("/proc/meminfo");
    ASSERT_TRUE(source.openSource());

    std::string data;
    EXPECT_TRUE(source.readSource(data));
    EXPECT_FALSE(data.empty());
}

TEST(FileTelemetrySourceImplTest, ReadProcMeminfo_ContainsMemTotal)
{
    FileTelemetrySourceImpl source("/proc/meminfo");
    ASSERT_TRUE(source.openSource());

    std::string data;
    ASSERT_TRUE(source.readSource(data));
    std::cout << data <<std::endl;

    // /proc/meminfo always has MemTotal
    EXPECT_NE(data.find("MemTotal"), std::string::npos);
}

TEST(FileTelemetrySourceImplTest, ReadProcMeminfo_ContainsMemFree)
{
    FileTelemetrySourceImpl source("/proc/meminfo");
    ASSERT_TRUE(source.openSource());

    std::string data;
    ASSERT_TRUE(source.readSource(data));

    EXPECT_NE(data.find("MemFree"), std::string::npos);
}

// ==================== Edge Case Tests ====================

TEST(FileTelemetrySourceImplTest, ReadBeforeOpen_Fails)
{
    FileTelemetrySourceImpl source("/proc/stat");
    std::string data;
    // File not opened yet, read should fail
    EXPECT_FALSE(source.readSource(data));
}

TEST(FileTelemetrySourceImplTest, OpenTwice_Succeeds)
{
    FileTelemetrySourceImpl source("/proc/stat");
    EXPECT_TRUE(source.openSource());
    // Opening again should still succeed (reopens the file)
    EXPECT_TRUE(source.openSource());
}

// ==================== ITelemetrySource Interface Tests ====================

TEST(FileTelemetrySourceImplTest, PolymorphicUsage_ProcStat)
{
    // Use through base interface pointer
    std::unique_ptr<ITelemetrySource> source =
        std::make_unique<FileTelemetrySourceImpl>("/proc/stat");

    ASSERT_TRUE(source->openSource());

    std::string data;
    ASSERT_TRUE(source->readSource(data));
    EXPECT_NE(data.find("cpu"), std::string::npos);

    std::cout << "=== /proc/stat (first 200 chars) ===" << std::endl;
    std::cout << data.substr(0, 200) << std::endl;
}

TEST(FileTelemetrySourceImplTest, PolymorphicUsage_ProcMeminfo)
{
    std::unique_ptr<ITelemetrySource> source =
        std::make_unique<FileTelemetrySourceImpl>("/proc/meminfo");

    ASSERT_TRUE(source->openSource());

    std::string data;
    ASSERT_TRUE(source->readSource(data));
    EXPECT_NE(data.find("MemTotal"), std::string::npos);

    std::cout << "=== /proc/meminfo (first 300 chars) ===" << std::endl;
    std::cout << data.substr(0, 300) << std::endl;
}
