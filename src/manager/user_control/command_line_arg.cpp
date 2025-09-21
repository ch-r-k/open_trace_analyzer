#include "command_line_arg.hpp"

namespace manager::user_control
{
CommandLineArgs::CommandLineArgs(int argc, const char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        args.emplace_back(argv[i]);
    }
}

// Get the raw list of arguments
const std::vector<std::string>& CommandLineArgs::getAll() const { return args; }

// Get argument by index (returns empty optional if out of range)
std::optional<std::string> CommandLineArgs::get(int index) const
{
    if (index >= 0 && index < (int)args.size()) return args[index];
    return std::nullopt;
}

// Check if a flag exists, e.g. "--help"
bool CommandLineArgs::hasFlag(const std::string& flag) const
{
    for (const auto& a : args)
    {
        if (a == flag) return true;
    }
    return false;
}

// Get value after a key, e.g. "--file myfile.txt"
std::optional<std::string> CommandLineArgs::getOption(
    const std::string& key) const
{
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args[i] == key && i + 1 < args.size())
        {
            return args[i + 1];
        }
    }
    return std::nullopt;
}

}  // namespace manager::user_control