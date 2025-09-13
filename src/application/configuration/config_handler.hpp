#pragma once

#include <string>
#include <memory>
#include "config_types.hpp"
#include "import/trace_files/txt_import/import_trace.hpp"
#include "import/trace_files/txt_import/txt_config/task_switch.hpp"
#include "import/trace_files/txt_import/txt_config/event_message.hpp"
#include "import/trace_files/txt_import/txt_config/state_machine.hpp"

namespace application::config
{
using application::import::txt_config::EventMessage;
using application::import::txt_config::StateMachine;
using application::import::txt_config::TaskSwitch;
using Json = nlohmann::json;

class ConfigHandler
{
   public:
    ConfigHandler(const std::string& filename);
    ~ConfigHandler() = default;

    std::string getTaskObjectFileName() const;
    std::string getTraceFileName() const;
    std::string getOutputFileName() const;

    OutputType getOutputFormat() const;
    InputType getInputFormat() const;

    EventMessage* getEventMessageConfig() const;
    StateMachine* getStateMachineConfig() const;
    TaskSwitch* getTaskSwitchConfig() const;

   private:
    Json json;
    std::string input_file{};
    std::string output_file{};
    std::string task_object_file{};
    InputType input_type{InputType::TXT};
    OutputType output_type{OutputType::PUML_SEQ};

    std::unique_ptr<EventMessage> event_message_config;
    std::unique_ptr<StateMachine> state_machine_config;
    std::unique_ptr<TaskSwitch> task_switch_config;

    void loadInputType();
    void loadOutputType();
    void loadFilePaths();
    void loadTxtConfig();
};

class ConfigurationException : public std::exception
{
   public:
    explicit ConfigurationException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override { return message.c_str(); }

   private:
    std::string message;
};

}  // namespace application::config