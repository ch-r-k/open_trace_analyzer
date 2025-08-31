#include "trace_entry.hpp"
#include <bits/c++config.h>

namespace application::trace_types
{
TraceEntry::TraceEntry(std::size_t line_number, std::uint64_t timestamp,
                       TraceType type)
    : line_number{line_number}, timestamp{timestamp}, type{type}
{
}

bool TraceEntry::operator<(const TraceEntry& other) const noexcept
{
    return line_number < other.line_number;
}

std::uint64_t TraceEntry::getTimestamp() { return timestamp; }

TraceEntry::TraceType TraceEntry::getType() const { return type; }

}  // namespace application::trace_types