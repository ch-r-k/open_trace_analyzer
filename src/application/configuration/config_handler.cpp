#include "config_handler.hpp"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "application/configuration/config_types.hpp"

namespace application::config
{
using Json = nlohmann::json;

ConfigHandler::ConfigHandler(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw ConfigurationException("Could not open config file: " + filename);
    }

    Json json;
    file >> json;

    // Required fields
    if (!json.contains("input_file_type") || !json.contains("output_file_type"))
    {
        throw ConfigurationException("Config file missing required fields");
    }

    // Parse input type
    std::string input_type_str = json["input_file_type"].get<std::string>();
    if (input_type_str == "txt")
    {
        input_type = InputType::TXT;
    }
    else if (input_type_str == "bin")
    {
        input_type = InputType::BIN;
    }
    else
    {
        throw ConfigurationException("Invalid input_file_type: " +
                                     input_type_str);
    }

    // Parse output type
    std::string output_type_str = json["output_file_type"].get<std::string>();
    if (output_type_str == "puml_sequence")
    {
        output_type = OutputType::PUML_SEQ;
    }
    else if (output_type_str == "puml_timing")
    {
        output_type = OutputType::PUML_TIMING;
    }
    else
    {
        throw ConfigurationException("Invalid output_file_type: " +
                                     output_type_str);
    }

    // files
    if (json.contains("input_file"))
    {
        input_file = json["input_file"].get<std::string>();
    }

    if (json.contains("output_file"))
    {
        output_file = json["output_file"].get<std::string>();
    }

    if (json.contains("task_object_file"))
    {
        task_object_file = json["task_object_file"].get<std::string>();
    }
}

std::string ConfigHandler::getTaskObjectFileName() const
{
    return task_object_file;
}

std::string ConfigHandler::getTraceFileName() const { return input_file; }

std::string ConfigHandler::getOutputFileName() const { return output_file; }

OutputType ConfigHandler::getOutputFormat() const { return output_type; }

InputType ConfigHandler::getInputFormat() const { return input_type; }

}  // namespace application::config
