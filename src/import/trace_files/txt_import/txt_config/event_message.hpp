#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"
#include "txt_config_exception.hpp"  // TxtImportException

namespace import::txt_config
{
using Json = nlohmann::json;

class EventMessage : public TxtConfig
{
   public:
    EventMessage(const std::string& regex, std::uint8_t pos_timestamp,
                 std::uint8_t pos_from, std::uint8_t pos_to,
                 std::uint8_t pos_text)
        : TxtConfig(regex, pos_timestamp),
          pos_from(pos_from),
          pos_to(pos_to),
          pos_text(pos_text)
    {
    }

    // Construct from JSON
    EventMessage(const Json& json)
    try : TxtConfig(json)
    {
        pos_from = extractGroupIndex(json, "task_from");
        pos_to = extractGroupIndex(json, "task_to");
        pos_text = extractGroupIndex(json, "message_text");
    }
    catch (const TxtImportException&)
    {
        throw;  // rethrow with original context
    }
    catch (const std::exception& e)
    {
        throw TxtImportException(
            std::string("Failed to construct EventMessage: ") + e.what());
    }

    bool operator==(const EventMessage& other) const
    {
        if (!TxtConfig::operator==(other)) return false;

        return pos_from == other.pos_from && pos_to == other.pos_to &&
               pos_text == other.pos_text;
    }

    std::uint8_t getFromPos() const { return pos_from; }
    std::uint8_t getToPos() const { return pos_to; }
    std::uint8_t getTextPos() const { return pos_text; }

   private:
    std::uint8_t pos_from{0};
    std::uint8_t pos_to{0};
    std::uint8_t pos_text{0};
};

}  // namespace import::txt_config
