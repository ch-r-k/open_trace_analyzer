#include "../command_line_arg.hpp"
#include <gtest/gtest.h>

using namespace manager::user_control;

class CommandLineArgsTest : public ::testing::Test
{
};

// ------------------------------------------------------------
// Constructor & getAll()
// ------------------------------------------------------------
TEST_F(CommandLineArgsTest, StoresAllArguments)
{
    const char* argv[] = {"program", "--flag", "value1"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    CommandLineArgs args(argc, argv);

    const auto& all = args.getAll();
    ASSERT_EQ(all.size(), 3);
    EXPECT_EQ(all[0], "program");
    EXPECT_EQ(all[1], "--flag");
    EXPECT_EQ(all[2], "value1");
}

// ------------------------------------------------------------
// get(index)
// ------------------------------------------------------------
TEST_F(CommandLineArgsTest, GetReturnsCorrectElement)
{
    const char* argv[] = {"program", "--opt", "file.txt"};
    int argc = 3;

    CommandLineArgs args(argc, argv);

    auto val0 = args.get(0);
    auto val1 = args.get(1);
    auto val2 = args.get(2);
    auto val3 = args.get(3);  // out of range

    ASSERT_TRUE(val0.has_value());
    ASSERT_TRUE(val1.has_value());
    ASSERT_TRUE(val2.has_value());
    EXPECT_EQ(val0.value(), "program");
    EXPECT_EQ(val1.value(), "--opt");
    EXPECT_EQ(val2.value(), "file.txt");

    EXPECT_FALSE(val3.has_value());  // index out of range
}

// ------------------------------------------------------------
// hasFlag()
// ------------------------------------------------------------
TEST_F(CommandLineArgsTest, HasFlagDetectsExistingFlags)
{
    const char* argv[] = {"program", "--help", "--verbose"};
    int argc = 3;

    CommandLineArgs args(argc, argv);

    EXPECT_TRUE(args.hasFlag("--help"));
    EXPECT_TRUE(args.hasFlag("--verbose"));
    EXPECT_FALSE(args.hasFlag("--missing"));
}

// ------------------------------------------------------------
// getOption()
// ------------------------------------------------------------
TEST_F(CommandLineArgsTest, GetOptionReturnsValueAfterKey)
{
    const char* argv[] = {"program", "--in", "input.txt", "--out",
                          "output.txt"};
    int argc = 5;

    CommandLineArgs args(argc, argv);

    auto in = args.getOption("--in");
    auto out = args.getOption("--out");
    auto none = args.getOption("--missing");

    ASSERT_TRUE(in.has_value());
    ASSERT_TRUE(out.has_value());
    EXPECT_EQ(in.value(), "input.txt");
    EXPECT_EQ(out.value(), "output.txt");
    EXPECT_FALSE(none.has_value());
}

TEST_F(CommandLineArgsTest, GetOptionHandlesKeyAtEnd)
{
    const char* argv[] = {"program", "--flag"};
    int argc = 2;

    CommandLineArgs args(argc, argv);

    auto val = args.getOption("--flag");
    EXPECT_FALSE(val.has_value());  // no value after key
}

TEST_F(CommandLineArgsTest, GetOptionReturnsFirstMatching)
{
    const char* argv[] = {"program", "--file", "a.txt", "--file", "b.txt"};
    int argc = 5;

    CommandLineArgs args(argc, argv);

    auto val = args.getOption("--file");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "a.txt");  // first occurrence
}
