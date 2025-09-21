#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>

namespace manager::user_control
{
class CommandLineArgs
{
   public:
    CommandLineArgs(int argc, const char* argv[]);

    const std::vector<std::string>& getAll() const;

    std::optional<std::string> get(int index) const;

    bool hasFlag(const std::string& flag) const;

    std::optional<std::string> getOption(const std::string& key) const;

   private:
    std::vector<std::string> args;
};

}  // namespace manager::user_control