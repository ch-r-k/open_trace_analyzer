#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include "txt_config_exception.hpp"  // TxtImportException

namespace import::txt_config
{
using Json = nlohmann::json;

class TxtConfig
{
   public:
    TxtConfig(const std::string& regex, std::uint8_t pos_timestamp)
        : regex(regex), pos_timestamp(pos_timestamp)
    {
    }

    // Construct from JSON object
    TxtConfig(const Json& json)
    try
    {
        // --- Validate required JSON members ---
        if (!json.contains("regex"))
        {
            throw TxtImportException(
                "TxtConfig: missing required field 'regex'");
        }

        if (!json.contains("groups"))
        {
            throw TxtImportException(
                "TxtConfig: missing required field 'groups'");
        }

        if (!json.at("groups").is_array())
        {
            throw TxtImportException("TxtConfig: 'groups' must be an array");
        }

        // Extract regex
        try
        {
            regex = json.at("regex").get<std::string>();
        }
        catch (const std::exception& e)
        {
            throw TxtImportException(
                std::string("TxtConfig: invalid 'regex' field: ") + e.what());
        }

        // Extract timestamp (validated inside extractGroupIndex)
        pos_timestamp = extractGroupIndex(json, "timestamp");
    }
    catch (const TxtImportException&)
    {
        throw;  // rethrow without modification
    }
    catch (const std::exception& e)
    {
        throw TxtImportException(
            std::string("TxtConfig: failed to construct from JSON: ") +
            e.what());
    }

    // Equality operator
    bool operator==(const TxtConfig& other) const
    {
        return regex == other.regex && pos_timestamp == other.pos_timestamp;
    }

    std::string getRegex() const { return regex; }
    std::uint8_t getTimestampPos() const { return pos_timestamp; }

   protected:
    std::string regex{};
    std::uint8_t pos_timestamp{0};

   protected:
    static std::uint8_t extractGroupIndex(const Json& json,
                                          const std::string& name)
    {
        if (!json.contains("groups"))
        {
            throw TxtImportException("TxtConfig: missing 'groups' array");
        }

        for (const auto& group : json.at("groups"))
        {
            if (!group.contains("name") || !group.contains("index"))
            {
                throw TxtImportException(
                    "TxtConfig: group entry missing 'name' or 'index'");
            }

            if (!group.at("name").is_string())
            {
                throw TxtImportException(
                    "TxtConfig: group 'name' must be a string");
            }

            if (!group.at("index").is_number_integer())
            {
                throw TxtImportException(
                    "TxtConfig: group 'index' must be an integer");
            }

            if (group.at("name").get<std::string>() == name)
            {
                int idx = group.at("index").get<int>();
                if (idx < 0 || idx > 255)
                    throw TxtImportException(
                        "TxtConfig: group index out of uint8_t range");

                return static_cast<std::uint8_t>(idx);
            }
        }

        throw TxtImportException("TxtConfig: could not find required group '" +
                                 name + "'");
    }
};

}  // namespace import::txt_config
