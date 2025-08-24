#include <gtest/gtest.h>
#include "application/manager.hpp"
#include <stdexcept>

using application::ApplicationManager;

// A simple test fixture (optional, useful if you want setup/teardown)
class UserInputHandlerTest : public ::testing::Test
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
TEST_F(UserInputHandlerTest, GetTaskObjectFileName)
{
    const char* argv[] = {"program",                                    //
                          "--in",     "src/test/input_files/qspy.txt",  //
                          "--out",    "src/test/output.puml",           //
                          "--config", "src/test/config.json",           //
                          "--tasks",  "src/test/input_files/qspy_ao.json"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    ApplicationManager app_manager{argc, argv};

    app_manager.execute();
}
