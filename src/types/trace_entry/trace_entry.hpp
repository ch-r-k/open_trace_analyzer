#pragma once

#include <bits/c++config.h>
#include <cstdint>
namespace types::trace
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

    TraceEntry(std::size_t line_number, std::uint64_t timestamp,
               TraceType type);
    virtual ~TraceEntry() = default;

    bool operator<(const TraceEntry& other) const noexcept;
    TraceType getType() const;
    std::uint64_t getTimestamp() const;
    double getTimestampUs() const;
    void adjustTimestamp(double conversion_factor);

   protected:
    std::size_t line_number;
    std::uint64_t timestamp;
    double timestamp_us{0};
    TraceType type;
};

}  // namespace types::trace