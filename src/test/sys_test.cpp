#include <gtest/gtest.h>
#include "manager/manager.hpp"
#include <stdexcept>

using manager::ApplicationManager;

// A simple test fixture (optional, useful if you want setup/teardown)
class SystemTest : public ::testing::Test
{
   protected:
    // You can initialize some common objects here
    void SetUp() override
    {
        // Called before each test
    }

    void TearDown() override
    {
        // Called after each test
    }
};

// Test a method (example)
TEST_F(SystemTest, analyze_test_file)
{
    const char* argv[] = {"program",  //
                          "--config", "src/test/input_files/config.json"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    ApplicationManager app_manager{argc, argv};

    app_manager.execute();
}

// Test a method (example)
TEST_F(SystemTest, generate_puml_sequence)
{
    const char* argv[] = {"program",  //
                          "--in",
                          "src/test/input_files/qspy_01.txt",  //
                          "--out",
                          "src/test/output_files/puml_01.txt",  //
                          "--config",
                          "src/test/input_files/config.json"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    ApplicationManager app_manager{argc, argv};

    app_manager.execute();
}
