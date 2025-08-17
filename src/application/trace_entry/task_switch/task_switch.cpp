#include "task_switch.hpp"
#include <bits/c++config.h>
#include <cstdint>
#include <iostream>
#include "application/trace_entry/trace_entry.hpp"

namespace application::trace_types
{
TaskSwitch::TaskSwitch(const std::size_t line_number,  //
                       const std::uint64_t timestamp,  //
                       const TaskObject& task_from,    //
                       const TaskObject& task_to)
    : TraceEntry{line_number, timestamp, TraceEntry::TraceType::TASK_SWITCH},
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