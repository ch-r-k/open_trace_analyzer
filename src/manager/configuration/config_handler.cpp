#include "config_handler.hpp"
#include <fstream>
#include <memory>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "config_types.hpp"
#include "import/trace_files/txt_import/txt_config/note.hpp"

namespace manager::config
{
ConfigHandler::ConfigHandler(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw ConfigurationException("Could not open config file: " + filename);
    }

    file >> json;

    // Required fields
    if (!json.contains("input_file_type") || !json.contains("output_file_type"))
    {
        throw ConfigurationException("Config file missing required fields");
    }

    loadInputType();

    loadOutputType();

    loadFilePaths();

    loadTxtConfig();
}

std::string ConfigHandler::getTaskObjectFileName() const
{
    return task_object_file;
}

std::string ConfigHandler::getTraceFileName() const { return input_file; }

std::string ConfigHandler::getOutputFileName() const { return output_file; }

OutputType ConfigHandler::getOutputFormat() const { return output_type; }

InputType ConfigHandler::getInputFormat() const { return input_type; }

EventMessage* ConfigHandler::getEventMessageConfig() const
{
    return event_message_config.get();
}

StateMachine* ConfigHandler::getStateMachineConfig() const
{
    return state_machine_config.get();
}

TaskSwitch* ConfigHandler::getTaskSwitchConfig() const
{
    return task_switch_config.get();
}

Note* ConfigHandler::getNoteConfig() const { return note_config.get(); }

void ConfigHandler::loadInputType()
{
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
}
void ConfigHandler::loadOutputType()
{
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
    else if (output_type_str == "open_trace_viewer")
    {
        output_type = OutputType::OPEN_TRACE_VIEWER;
    }
    else
    {
        throw ConfigurationException("Invalid output_file_type: " +
                                     output_type_str);
    }
}

void ConfigHandler::loadFilePaths()
{
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

void ConfigHandler::loadTxtConfig()
{
    if ((json.contains("txt_config")) && (input_type == InputType::TXT))
    {
        const auto& txt_cfg = json["txt_config"];

        task_switch_config =
            std::make_unique<TaskSwitch>(txt_cfg["task_switch"]);

        state_machine_config =
            std::make_unique<StateMachine>(txt_cfg["state_machine"]);

        event_message_config =
            std::make_unique<EventMessage>(txt_cfg["event_message"]);

        note_config = std::make_unique<Note>(txt_cfg["note"]);
    }
    else
    {
        throw ConfigurationException("Missing TXT config");
    }
}

}  // namespace manager::config
