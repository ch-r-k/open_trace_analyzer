#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>

namespace application::config::txt
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
    TxtConfig(const Json& j)
    {
        regex = j.at("regex").get<std::string>();
        pos_timestamp = extractGroupIndex(j, "timestamp");
    }

    // Equality operator
    bool operator==(const TxtConfig& other) const
    {
        return regex == other.regex && pos_timestamp == other.pos_timestamp;
    }

   protected:
    std::string regex{};
    std::uint8_t pos_timestamp{0};

   protected:
    static std::uint8_t extractGroupIndex(const Json& json,
                                          const std::string& name)
    {
        for (auto& group : json.at("groups"))
        {
            if (group.at("name") == name)
            {
                return static_cast<std::uint8_t>(group.at("index").get<int>());
            }
        }
        return 0;
    }
};

}  // namespace application::config::txt
