#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>

#include "command_line_arg.hpp"

namespace manager::user_control
{
class UserInputHandler
{
   public:
    UserInputHandler(int argc, const char* argv[]);

    std::string getTaskObjectFileName() const;
    std::string getTraceFileName() const;
    std::string getOutputFileName() const;
    std::string getConfigFileName() const;
    double getTimestampScalingFactor() const;

   private:
    void handleConfigFile();
    void handleTraceInputFile();
    void handleTasksFile();
    void handleOutputFile();
    CommandLineArgs cmd_args;

    bool help{false};
    bool config{false};
    bool file_names{false};

    std::string trace_input_file_name{};
    std::string tasks_input_file_name{};
    std::string config_file_name{};
    std::string output_file_name{};
    double timestamp_scaling_factor;

    static std::string helpMessage();
};

class UserInputException : public std::exception
{
   public:
    explicit UserInputException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override { return message.c_str(); }

   private:
    std::string message;
};

}  // namespace manager::user_control