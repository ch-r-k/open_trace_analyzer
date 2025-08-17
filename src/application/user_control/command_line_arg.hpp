#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>

namespace application::user_control
{
class CommandLineArgs
{
   public:
    CommandLineArgs(int argc, char* argv[]);

    const std::vector<std::string>& getAll() const;

    std::optional<std::string> get(int index) const;

    bool hasFlag(const std::string& flag) const;

    std::optional<std::string> getOption(const std::string& key) const;

   private:
    std::vector<std::string> args;
};

}  // namespace application::user_control