#pragma once

#include <cstdint>
#include <string>

namespace manager::config
{
enum class InputType
{
    TXT = 0,
    BIN
};

enum class OutputType
{
    PUML_SEQ = 0,
    PUML_TIMING,
    OPEN_TRACE_VIEWER
};

class TextDecoder
{
   public:
    TextDecoder(std::string regex, std::uint8_t pos_timestamp);

   protected:
    std::string regex{};
    std::uint8_t pos_timestamp{0};
};

}  // namespace manager::config