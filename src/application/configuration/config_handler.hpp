#pragma once

#include <string>
#include "config_types.hpp"

namespace application::config
{
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

   private:
    std::string input_file{};
    std::string output_file{};
    std::string task_object_file{};
    InputType input_type{InputType::TXT};
    OutputType output_type{OutputType::PUML_SEQ};
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