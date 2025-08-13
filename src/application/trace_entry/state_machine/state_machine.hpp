#pragma once

#include <cstdint>
#include <string_view>
#include "../trace_entry.hpp"
#include "application/task_object/task_object.hpp"

namespace application::trace_types
{
using task_types::TaskObject;

class StateMachine : public TraceEntry
{
   public:
    StateMachine(std::uint64_t timestamp, TaskObject& task,
                 std::string_view state_name);
    ~StateMachine() = default;

    friend std::ostream& operator<<(std::ostream& os, const StateMachine& p);

   private:
    TaskObject& task;
    std::string_view state_name;
};

}  // namespace application::trace_types