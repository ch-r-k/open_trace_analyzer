#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"

namespace application::config::txt
{
using Json = nlohmann::json;

struct TaskSwitch : public TxtConfig
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

   private:
    std::uint8_t pos_from{0};
    std::uint8_t pos_to{0};
};

}  // namespace application::config::txt
