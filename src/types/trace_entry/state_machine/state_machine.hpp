#pragma once

#include <bits/c++config.h>
#include <cstdint>
#include <string>
#include "../trace_entry.hpp"
#include "types/task_object/task_object.hpp"

namespace types::trace
{
using types::task::TaskObject;

class StateMachine : public TraceEntry
{
   public:
    StateMachine(const std::size_t line_number,  //
                 const std::uint64_t timestamp,  //
                 const TaskObject& task,         //
                 std::string state_name);
    ~StateMachine() = default;

    TaskObject getTask();
    std::string getState();
    friend std::ostream& operator<<(std::ostream& os, const StateMachine& p);

   private:
    TaskObject task;
    std::string state_name;
};

}  // namespace types::trace