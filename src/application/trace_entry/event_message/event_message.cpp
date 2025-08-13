#include <cstdint>
#include <iostream>
#include "event_message.hpp"
#include "application/trace_entry/trace_entry.hpp"

namespace application::trace_types
{
EventMessage::EventMessage(std::uint64_t timestamp, TaskObject& task_from,
                           TaskObject& task_to, std::string_view text)
    : TraceEntry{timestamp, TraceEntry::TraceType::EVENT_MESSAGE},
      task_from{task_to},
      task_to{task_from},
      text{text}
{
}

std::ostream& operator<<(std::ostream& os, const EventMessage& p)
{
    os << "Timestamp: " << p.timestamp  //
       << ", From: " << p.task_from     //
       << ", To: " << p.task_to         //
       << ", Message: " << p.text;      //
    return os;
}

}  // namespace application::trace_types