#include "task_switch.hpp"
#include <cstdint>
#include <iostream>
#include "application/trace_entry/trace_entry.hpp"

namespace application::trace_types
{
TaskSwitch::TaskSwitch(std::uint64_t timestamp, TaskObject& task_from,
                       TaskObject& task_to)
    : TraceEntry{timestamp, TraceEntry::TraceType::TASK_SWITCH},
      task_from{task_from},
      task_to{task_to}
{
}

std::ostream& operator<<(std::ostream& os, const TaskSwitch& p)
{
    os << "Timestamp: " << p.timestamp  //
       << ", From: " << p.task_from     //
       << ", To: " << p.task_to;        //
    return os;
}

}  // namespace application::trace_types