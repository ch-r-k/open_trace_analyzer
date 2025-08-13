#pragma once

#include <cstdint>
namespace application::trace_types
{
class TraceEntry
{
   public:
    enum class TraceType : std::uint8_t
    {
        NONE = 0,
        TASK_SWITCH,
        EVENT_MESSAGE,
        USER_MESSAGE,
        STATE_MACHINE,
    };

    TraceEntry(std::uint64_t timestamp, TraceType type);
    ~TraceEntry() = default;

   protected:
    std::uint64_t timestamp;
    TraceType type;
};

}  // namespace application::trace_types