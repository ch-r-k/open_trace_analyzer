#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"

namespace application::import::txt_config
{
using Json = nlohmann::json;

class StateMachine : public TxtConfig
{
   public:
    StateMachine(const std::string& regex,    //
                 std::uint8_t pos_timestamp,  //
                 std::uint8_t pos_task,       //
                 std::uint8_t pos_state)      //
        : TxtConfig(regex, pos_timestamp),
          pos_task(pos_task),
          pos_state(pos_state)
    {
    }

    // Construct from JSON
    StateMachine(const Json& json)
        : TxtConfig(json),
          pos_task(extractGroupIndex(json, "task")),
          pos_state(extractGroupIndex(json, "state_name"))
    {
    }

    bool operator==(const StateMachine& other) const
    {
        // Compare base TxtConfig first
        if (!TxtConfig::operator==(other)) return false;

        // Compare EventMessage-specific members
        return pos_state == other.pos_state && pos_task == other.pos_task;
    }

   private:
    std::uint8_t pos_task{0};
    std::uint8_t pos_state{0};
};

}  // namespace application::import::txt_config
