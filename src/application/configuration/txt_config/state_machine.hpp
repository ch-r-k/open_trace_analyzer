#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"

namespace application::config::txt
{
using Json = nlohmann::json;

struct StateMachine : public TxtConfig
{
   public:
    StateMachine(const std::string& regex, std::uint8_t pos_timestamp,
                 std::uint8_t pos_state)
        : TxtConfig(regex, pos_timestamp), pos_state(pos_state)
    {
    }

    // Construct from JSON
    StateMachine(const Json& json)
        : TxtConfig(json), pos_state(extractGroupIndex(json, "state_name"))
    {
    }

   private:
    std::uint8_t pos_state{0};
};

}  // namespace application::config::txt
