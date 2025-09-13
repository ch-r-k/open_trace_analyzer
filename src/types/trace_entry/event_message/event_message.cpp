#include <cstddef>
#include <cstdint>
#include <iostream>
#include "event_message.hpp"
#include "../trace_entry.hpp"

namespace types::trace
{
EventMessage::EventMessage(const size_t line_number,       //
                           const std::uint64_t timestamp,  //
                           const TaskObject& task_from,    //
                           const TaskObject& task_to,      //
                           std::string text)
    : TraceEntry{line_number, timestamp, TraceEntry::TraceType::EVENT_MESSAGE},
      task_from{task_from},
      task_to{task_to},
      text{text}
{
}

TaskObject EventMessage::getFrom() { return task_from; };
TaskObject EventMessage::getTo() { return task_to; };
std::string EventMessage::getText() { return text; };

std::ostream& operator<<(std::ostream& os, const EventMessage& p)
{
    os << "Timestamp: " << p.timestamp  //
       << ", From: " << p.task_from     //
       << ", To: " << p.task_to         //
       << ", Message: " << p.text;      //
    return os;
}

}  // namespace types::trace