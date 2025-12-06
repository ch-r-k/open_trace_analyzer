#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"
#include "txt_config_exception.hpp"

namespace import::txt_config
{
using Json = nlohmann::json;

class StateMachine : public TxtConfig
{
   public:
    StateMachine(const std::string& regex,    //
                 std::uint8_t pos_timestamp,  //
                 std::uint8_t pos_task,       //
                 std::uint8_t pos_state)
        : TxtConfig(regex, pos_timestamp),
          pos_task(pos_task),
          pos_state(pos_state)
    {
    }

    // Construct from JSON
    StateMachine(const Json& json)
    try : TxtConfig(json)  // Validates: regex, timestamp, groups
    {
        pos_task = extractGroupIndex(json, "task");
        pos_state = extractGroupIndex(json, "state_name");
    }
    catch (const TxtImportException&)
    {
        throw;  // pass through unchanged
    }
    catch (const std::exception& e)
    {
        throw TxtImportException(
            std::string("Failed to construct StateMachine: ") + e.what());
    }

    bool operator==(const StateMachine& other) const
    {
        if (!TxtConfig::operator==(other)) return false;

        return pos_state == other.pos_state && pos_task == other.pos_task;
    }

    std::uint8_t getTaskPos() const { return pos_task; }
    std::uint8_t getStatePos() const { return pos_state; }

   private:
    std::uint8_t pos_task{0};
    std::uint8_t pos_state{0};
};

}  // namespace import::txt_config
