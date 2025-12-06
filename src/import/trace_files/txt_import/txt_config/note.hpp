#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config.hpp"
#include "txt_config_exception.hpp"

namespace import::txt_config
{
using Json = nlohmann::json;

class Note : public TxtConfig
{
   public:
    Note(const std::string& regex, std::uint8_t pos_timestamp,
         std::uint8_t pos_text)
        : TxtConfig(regex, pos_timestamp), pos_text(pos_text)
    {
    }

    // Construct from JSON
    Note(const Json& json)
    try : TxtConfig(json)  // Validates regex, timestamp, groups array
    {
        pos_text = extractGroupIndex(json, "text");
    }
    catch (const TxtImportException&)
    {
        throw;  // keep original context
    }
    catch (const std::exception& e)
    {
        throw TxtImportException(std::string("Failed to construct Note: ") +
                                 e.what());
    }

    bool operator==(const Note& other) const
    {
        if (!TxtConfig::operator==(other))
        {
            return false;
        }

        return pos_text == other.pos_text;
    }

    std::uint8_t getTextPos() const { return pos_text; }

   private:
    std::uint8_t pos_text{0};
};

}  // namespace import::txt_config
