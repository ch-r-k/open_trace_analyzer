#include "../user_input_handler.hpp"
#include <gtest/gtest.h>

namespace test
{

using namespace manager::user_control;

class UserInputHandlerTest : public ::testing::Test
{
};

// ------------------------------------------------------------
// Normal usage with all files specified
// ------------------------------------------------------------
TEST_F(UserInputHandlerTest, ParsesAllFilesCorrectly)
{
    const char* argv[] = {"program", "--in",      "trace.txt",
                          "--tasks", "tasks.txt", "--out",
                          "out.txt", "--config",  "config.json"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    UserInputHandler handler(argc, argv);

    EXPECT_EQ(handler.getTraceFileName(), "trace.txt");
    EXPECT_EQ(handler.getTaskObjectFileName(), "tasks.txt");
    EXPECT_EQ(handler.getOutputFileName(), "out.txt");
    EXPECT_EQ(handler.getConfigFileName(), "config.json");
}

// ------------------------------------------------------------
// Missing optional files (--in, --tasks, --out)
// ------------------------------------------------------------
TEST_F(UserInputHandlerTest, SetsEmptyStringsForMissingOptionalFiles)
{
    const char* argv[] = {"program", "--config", "config.json"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    UserInputHandler handler(argc, argv);

    EXPECT_EQ(handler.getTraceFileName(), "");
    EXPECT_EQ(handler.getTaskObjectFileName(), "");
    EXPECT_EQ(handler.getOutputFileName(), "");
    EXPECT_EQ(handler.getConfigFileName(), "config.json");
}

// ------------------------------------------------------------
// Missing required --config file
// ------------------------------------------------------------
TEST_F(UserInputHandlerTest, ThrowsExceptionIfConfigMissing)
{
    const char* argv[] = {"program"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_THROW({ UserInputHandler handler(argc, argv); }, UserInputException);
}

// ------------------------------------------------------------
// --help flag sets help = true
// ------------------------------------------------------------
TEST_F(UserInputHandlerTest, HelpFlagPrintsHelpMessage)
{
    const char* argv[] = {"program", "--help"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    // Redirect std::cout to a stringstream
    std::stringstream buffer;
    std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());

    // Run the handler
    UserInputHandler handler(argc, argv);

    // Restore std::cout
    std::cout.rdbuf(old_cout);

    // Check that the buffer contains the help message
    std::string output = buffer.str();
    EXPECT_NE(output.find("Usage:"), std::string::npos);
    EXPECT_NE(output.find("--help"), std::string::npos);
    EXPECT_NE(output.find("--in <file>"), std::string::npos);
    EXPECT_NE(output.find("--out <file>"), std::string::npos);
    EXPECT_NE(output.find("--config <file>"), std::string::npos);
}

// ------------------------------------------------------------
// Partial options set
// ------------------------------------------------------------
TEST_F(UserInputHandlerTest, PartialOptions)
{
    const char* argv[] = {"program", "--in", "trace.txt", "--config",
                          "cfg.json"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    UserInputHandler handler(argc, argv);

    EXPECT_EQ(handler.getTraceFileName(), "trace.txt");
    EXPECT_EQ(handler.getTaskObjectFileName(), "");
    EXPECT_EQ(handler.getOutputFileName(), "");
    EXPECT_EQ(handler.getConfigFileName(), "cfg.json");
}

}  // namespace test