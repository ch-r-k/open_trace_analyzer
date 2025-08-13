#include "trace_entry.hpp"

namespace application::trace_types
{
TraceEntry::TraceEntry(std::uint64_t timestamp, TraceType type)
    : timestamp{timestamp}, type{type}
{
}

}  // namespace application::trace_types