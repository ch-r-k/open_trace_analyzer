#include <gtest/gtest.h>
#include "manager/manager.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

namespace test
{

using manager::ApplicationManager;

// Helper function to compare two text files
void compareFiles(const std::string& generated_file,
                  const std::string& expected_file)
{
    std::ifstream gen(generated_file);
    std::ifstream exp(expected_file);

    ASSERT_TRUE(gen.is_open())
        << "Could not open generated file: " << generated_file;
    ASSERT_TRUE(exp.is_open())
        << "Could not open expected file: " << expected_file;

    std::ostringstream gen_buf, exp_buf;
    gen_buf << gen.rdbuf();
    exp_buf << exp.rdbuf();

    std::string gen_str = gen_buf.str();
    std::string exp_str = exp_buf.str();

    // Normalize line endings (for Windows/Linux cross-platform consistency)
    auto normalize = [](std::string& s)
    { s.erase(std::remove(s.begin(), s.end(), '\r'), s.end()); };
    normalize(gen_str);
    normalize(exp_str);

    EXPECT_EQ(gen_str, exp_str)
        << "Generated file does not match expected file:\n"
        << "Generated: " << generated_file << "\nExpected:  " << expected_file;
}

// A simple test fixture (optional, useful if you want setup/teardown)
class SystemTest : public ::testing::Test
{
   protected:
    // Common file paths for each test
    std::string input_file;
    std::string output_file;
    std::string config_file;
    std::string expected_file;

    // argv template, all placeholders
    std::vector<const char*> argv_template = {
        "program", "--in", nullptr, "--out", nullptr, "--config", nullptr};

    void SetUp() override
    {
        // Default config file if you want
        config_file = "src/test/input_files/config.json";
    }

    void TearDown() override
    {
        if (!output_file.empty() && !expected_file.empty())
        {
            compareFiles(output_file, expected_file);
        }
    }

    // Helper to build argv dynamically
    std::vector<const char*> makeArgv()
    {
        std::vector<const char*> argv;
        for (size_t i = 0; i < argv_template.size(); ++i)
        {
            const char* arg = argv_template[i];
            if (arg != nullptr)
            {
                argv.push_back(arg);
            }
            else
            {
                // Insert the right placeholder
                if (i >= 2 && std::strcmp(argv_template[i - 1], "--in") == 0)
                    argv.push_back(input_file.c_str());
                else if (i >= 2 &&
                         std::strcmp(argv_template[i - 1], "--out") == 0)
                    argv.push_back(output_file.c_str());
                else if (i >= 2 &&
                         std::strcmp(argv_template[i - 1], "--config") == 0)
                    argv.push_back(config_file.c_str());
                else
                    argv.push_back("");  // just in case
            }
        }
        return argv;
    }
};

TEST_F(SystemTest, analyze_test_file)
{
    // Only config is relevant in this test
    config_file = "src/test/input_files/config_open_trace_viewer.json";

    // You can leave input/output/expected empty if not needed
    input_file.clear();
    output_file.clear();
    expected_file.clear();

    // Build argv using placeholders
    auto argv_vec = makeArgv();
    int argc = static_cast<int>(argv_vec.size());

    ApplicationManager app_manager{argc, argv_vec.data()};
    app_manager.execute();
}

TEST_F(SystemTest, generate_puml_sequence)
{
    input_file = "src/test/input_files/qspy_01.txt";
    output_file = "src/test/output_files/puml_01.txt";
    expected_file = "src/test/expected_outputs/puml_01.txt";
    config_file = "src/test/input_files/config_puml_sequence.json";

    auto argv_vec = makeArgv();
    int argc = static_cast<int>(argv_vec.size());

    {
        ApplicationManager app_manager{argc, argv_vec.data()};
        app_manager.execute();
    }
}

TEST_F(SystemTest, generate_puml_timing)
{
    input_file = "src/test/input_files/qspy_01.txt";
    output_file = "src/test/output_files/puml_02.txt";
    expected_file = "src/test/expected_outputs/puml_02.txt";
    config_file = "src/test/input_files/config_puml_timing.json";

    auto argv_vec = makeArgv();
    int argc = static_cast<int>(argv_vec.size());

    {
        ApplicationManager app_manager{argc, argv_vec.data()};
        app_manager.execute();
    }
}

TEST_F(SystemTest, generate_open_trace_viewer)
{
    input_file = "src/test/input_files/qspy_01.txt";
    output_file = "src/test/output_files/open_trace_viewer.json";
    expected_file = "src/test/expected_outputs/open_trace_viewer.json";
    config_file = "src/test/input_files/config_open_trace_viewer.json";

    auto argv_vec = makeArgv();
    int argc = static_cast<int>(argv_vec.size());

    {
        ApplicationManager app_manager{argc, argv_vec.data()};
        app_manager.execute();
    }
}

}  // namespace test
