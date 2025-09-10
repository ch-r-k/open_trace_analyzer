#include <gtest/gtest.h>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "../config_handler.hpp"

using namespace application::config;
using Json = nlohmann::json;

TEST(ConfigHandlerTest, ThrowsIfFileMissing)
{
    EXPECT_THROW({ ConfigHandler handler("non_existent_file.json"); },
                 ConfigurationException);
}

TEST(ConfigHandlerTest, ThrowsIfMissingRequiredFields)
{
    std::string filename =
        "src/application/configuration/test/no_input_file.json";

    EXPECT_THROW({ ConfigHandler handler(filename); }, ConfigurationException);
}

TEST(ConfigHandlerTest, ThrowsOnInvalidInputType)
{
    std::string filename =
        "src/application/configuration/test/invalid_input_type.json";
    EXPECT_THROW({ ConfigHandler handler(filename); }, ConfigurationException);
}

TEST(ConfigHandlerTest, ThrowsOnInvalidOutputType)
{
    std::string filename =
        "src/application/configuration/test/invalid_output_type.json";
    EXPECT_THROW({ ConfigHandler handler(filename); }, ConfigurationException);
}

TEST(ConfigHandlerTest, LoadsValidConfigWithAllFields)
{
    std::string filename =
        "src/application/configuration/test/valid_config.json";

    ConfigHandler handler(filename);

    EXPECT_EQ(handler.getInputFormat(), InputType::TXT);
    EXPECT_EQ(handler.getOutputFormat(), OutputType::PUML_SEQ);
    EXPECT_EQ(handler.getTraceFileName(), "trace.txt");
    EXPECT_EQ(handler.getOutputFileName(), "out.puml");
    EXPECT_EQ(handler.getTaskObjectFileName(), "tasks.json");
}

TEST(ConfigHandlerTest, MissingOptionalFieldsDefaultsToEmptyStrings)
{
    std::string filename =
        "src/application/configuration/test/valid_config_defaults.json";

    ConfigHandler handler(filename);

    EXPECT_EQ(handler.getTraceFileName(), "");
    EXPECT_EQ(handler.getOutputFileName(), "");
    EXPECT_EQ(handler.getTaskObjectFileName(), "");
}
