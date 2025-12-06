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
    if (input_type != InputType::TXT)
    {
        loadDefaultTxtConfig();
        return;
    }

    if (!json.contains("txt_config"))
    {
        loadDefaultTxtConfig();
        return;
    }

    const auto& txt_cfg = json["txt_config"];

    try
    {
        // task_switch
        if (txt_cfg.contains("task_switch"))
        {
            task_switch_config =
                std::make_unique<TaskSwitch>(txt_cfg["task_switch"]);
        }
        else
        {
            task_switch_config = loadDefaultTaskSwitch();
        }

        // state_machine
        if (txt_cfg.contains("state_machine"))
        {
            state_machine_config =
                std::make_unique<StateMachine>(txt_cfg["state_machine"]);
        }
        else
        {
            state_machine_config = loadDefaultStateMachine();
        }

        // event_message
        if (txt_cfg.contains("event_message"))
        {
            event_message_config =
                std::make_unique<EventMessage>(txt_cfg["event_message"]);
        }
        else
        {
            event_message_config = loadDefaultEventMessage();
        }

        // note
        if (txt_cfg.contains("note"))
        {
            note_config = std::make_unique<Note>(txt_cfg["note"]);
        }
        else
        {
            note_config = loadDefaultNote();
        }
    }
    catch (const std::exception& e)
    {
        throw ConfigurationException(std::string("Invalid txt config: ") +
                                     e.what());
    }
}

void ConfigHandler::loadDefaultTxtConfig()
{
    task_switch_config = loadDefaultTaskSwitch();
    state_machine_config = loadDefaultStateMachine();
    event_message_config = loadDefaultEventMessage();
    note_config = loadDefaultNote();
}

std::unique_ptr<TaskSwitch> ConfigHandler::loadDefaultTaskSwitch()
{
    return std::make_unique<TaskSwitch>(
        "^\\s*(\\d+)\\s+(Sch-(Next|Idle))\\s+Pri=(\\d+)->(\\d+)",  //
        1,                                                         //
        4,                                                         //
        5);                                                        //
}

std::unique_ptr<StateMachine> ConfigHandler::loadDefaultStateMachine()
{
    return std::make_unique<StateMachine>(
        "^\\s*(\\d+)\\s+===\\>Tran\\s+Obj=([^,]+),.*State=[^>]+->([^,]+)",  //
        1,                                                                  //
        2,                                                                  //
        3);
}

std::unique_ptr<EventMessage> ConfigHandler::loadDefaultEventMessage()
{
    return std::make_unique<EventMessage>(
        "^\\s*(\\d+).*AO-Post.*Sdr=([^,]+),Obj=([^,]+).*Sig=([^,>]+)",  //
        1,                                                              //
        2,                                                              //
        3,                                                              //
        4);                                                             //
}

std::unique_ptr<Note> ConfigHandler::loadDefaultNote()
{
    return std::make_unique<Note>("^(\\d{10})\\s+(.*)$",  //
                                  1,                      //
                                  2);                     //
}

}  // namespace manager::config
