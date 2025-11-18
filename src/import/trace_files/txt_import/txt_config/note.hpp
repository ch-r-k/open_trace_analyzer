#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"

namespace import::txt_config
{
using Json = nlohmann::json;

class Note : public TxtConfig
{
   public:
    Note(const std::string& regex,    //
         std::uint8_t pos_timestamp,  //
         std::uint8_t pos_text)
        : TxtConfig(regex, pos_timestamp),  //
          pos_text(pos_text)
    {
    }

    // Construct from JSON
    Note(const Json& json)
        : TxtConfig(json),  //
          pos_text(extractGroupIndex(json, "text"))
    {
    }

    bool operator==(const Note& other) const
    {
        // Compare base TxtConfig first
        if (!TxtConfig::operator==(other)) return false;

        // Compare EventMessage-specific members
        return pos_text == other.pos_text;
    }

    std::uint8_t getTextPos() { return pos_text; };

   private:
    std::uint8_t pos_text{0};
};

}  // namespace import::txt_config
