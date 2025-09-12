#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"

namespace application::import::txt_config
{
using Json = nlohmann::json;

class TaskSwitch : public TxtConfig
{
   public:
    TaskSwitch(const std::string& regex, std::uint8_t pos_timestamp,
               std::uint8_t pos_from, std::uint8_t pos_to)
        : TxtConfig(regex, pos_timestamp), pos_from(pos_from), pos_to(pos_to)
    {
    }

    // Construct from JSON
    TaskSwitch(const Json& json)
        : TxtConfig(json),
          pos_from(extractGroupIndex(json, "task_from")),
          pos_to(extractGroupIndex(json, "task_to"))
    {
    }

    bool operator==(const TaskSwitch& other) const
    {
        // Compare base TxtConfig first
        if (!TxtConfig::operator==(other)) return false;

        // Compare EventMessage-specific members
        return pos_from == other.pos_from && pos_to == other.pos_to;
    }

    std::uint8_t getFromPos() { return pos_from; };
    std::uint8_t getToPos() { return pos_to; };

   private:
    std::uint8_t pos_from{0};
    std::uint8_t pos_to{0};
};

}  // namespace application::import::txt_config
