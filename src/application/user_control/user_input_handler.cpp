#include "user_input_handler.hpp"
#include <iostream>

namespace application::user_control
{
UserInputHandler::UserInputHandler(int argc, const char* argv[])
    : cmd_args{argc, argv}
{
    help = cmd_args.hasFlag("--help");

    if (help)
    {
        std::cout << helpMessage();
    }
    else
    {
        handleTraceInputFile();
        handleTasksFile();
        handleOutputFile();
        handleConfigFile();
    }
}

void UserInputHandler::handleTraceInputFile()
{
    std::optional<std::string> maybe_name = cmd_args.getOption("--in");

    if (maybe_name)
    {
        trace_input_file_name = *maybe_name;
    }
    else
    {
        trace_input_file_name = "";
    }
}

void UserInputHandler::handleTasksFile()
{
    std::optional<std::string> maybe_name = cmd_args.getOption("--tasks");

    if (maybe_name)
    {
        tasks_input_file_name = *maybe_name;
    }
    else
    {
        tasks_input_file_name = "";
    }
}

void UserInputHandler::handleOutputFile()
{
    std::optional<std::string> maybe_name = cmd_args.getOption("--out");

    if (maybe_name)
    {
        output_file_name = *maybe_name;
    }
    else
    {
        output_file_name = "";
    }
}

void UserInputHandler::handleConfigFile()
{
    std::optional<std::string> maybe_name = cmd_args.getOption("--config");

    if (maybe_name)
    {
        config_file_name = *maybe_name;
    }
    else
    {
        throw UserInputException("Invalid input: No Config file name");
    }
}

std::string UserInputHandler::helpMessage()
{
    return "Usage:\n"
           "  program --in <file> --out <file> --tasks <file> --config "
           "<configfile>\n"
           "  program --config <configfile>\n\n"
           "Options:\n"
           "  --help          Show this help message\n"
           "  --in <file>     Input trace file\n"
           "  --out <file>    Output file\n"
           "  --task <file>   Task object file\n"
           "  --config <file> Configuration file\n";
}

std::string UserInputHandler::getTaskObjectFileName() const
{
    return tasks_input_file_name;
}

std::string UserInputHandler::getTraceFileName() const
{
    return trace_input_file_name;
}

std::string UserInputHandler::getOutputFileName() const
{
    return output_file_name;
};

}  // namespace application::user_control