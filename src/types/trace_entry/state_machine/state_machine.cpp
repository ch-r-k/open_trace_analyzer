#include <bits/c++config.h>
#include <cstdint>
#include <iostream>
#include "state_machine.hpp"
#include "types/trace_entry/trace_entry.hpp"

namespace types::trace
{
StateMachine::StateMachine(std::size_t line_number,        //
                           const std::uint64_t timestamp,  //
                           const TaskObject& task,         //
                           std::string state_name)
    : TraceEntry{line_number, timestamp, TraceEntry::TraceType::STATE_MACHINE},
      task{task},
      state_name{state_name}
{
}

TaskObject StateMachine::getTask() { return task; }

std::string StateMachine::getState() { return state_name; }

std::ostream& operator<<(std::ostream& os, const StateMachine& p)
{
    os << "Timestamp: " << p.timestamp  //
       << ", Task: " << p.task          //
       << ", State: " << p.state_name;  //
    return os;
}
}  // namespace types::trace