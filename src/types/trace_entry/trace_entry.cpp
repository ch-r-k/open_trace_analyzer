#include "trace_entry.hpp"
#include <bits/c++config.h>

namespace types::trace
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

std::uint64_t TraceEntry::getTimestamp() const { return timestamp; }

TraceEntry::TraceType TraceEntry::getType() const { return type; }

void TraceEntry::adjustTimestamp(double conversion_factor)
{
    timestamp_us = static_cast<double>(timestamp) * conversion_factor;
}

double TraceEntry::getTimestampUs() const { return timestamp_us; }

}  // namespace types::trace