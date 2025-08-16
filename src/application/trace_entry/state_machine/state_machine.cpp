#include <cstdint>
#include <iostream>
#include "state_machine.hpp"
#include "application/trace_entry/trace_entry.hpp"

namespace application::trace_types
{
StateMachine::StateMachine(std::uint64_t timestamp, const TaskObject& task,
                           std::string state_name)
    : TraceEntry{timestamp, TraceEntry::TraceType::STATE_MACHINE},
      task{task},
      state_name{state_name}
{
}

std::ostream& operator<<(std::ostream& os, const StateMachine& p)
{
    os << "Timestamp: " << p.timestamp  //
       << ", Task: " << p.task          //
       << ", State: " << p.state_name;  //
    return os;
}
}  // namespace application::trace_types