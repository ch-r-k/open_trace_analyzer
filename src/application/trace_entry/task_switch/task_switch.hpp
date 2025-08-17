#pragma once

#include <bits/c++config.h>
#include <cstdint>
#include "../trace_entry.hpp"
#include "application/task_object/task_object.hpp"

namespace application::trace_types
{
using task_types::TaskObject;

class TaskSwitch : public TraceEntry
{
   public:
    TaskSwitch(const std::size_t line_number,  //
               const std::uint64_t timestamp,  //
               const TaskObject& task_from,    //
               const TaskObject& task_to);
    ~TaskSwitch() = default;

    friend std::ostream& operator<<(std::ostream& os, const TaskSwitch& p);

   private:
    TaskObject task_from;
    TaskObject task_to;
};

}  // namespace application::trace_types