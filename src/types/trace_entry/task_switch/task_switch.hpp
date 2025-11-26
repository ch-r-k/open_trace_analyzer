#pragma once

#include <bits/c++config.h>
#include <cstdint>
#include "../trace_entry.hpp"
#include "types/task_object/task_object.hpp"

namespace types::trace
{
using types::task::TaskObject;

class TaskSwitch : public TraceEntry
{
   public:
    TaskSwitch(const std::size_t line_number,  //
               const std::uint64_t timestamp,  //
               const TaskObject& task_from,    //
               const TaskObject& task_to);
    ~TaskSwitch() = default;

    friend std::ostream& operator<<(std::ostream& os, const TaskSwitch& p);

    TaskObject getFrom() const;
    TaskObject getTo() const;

   private:
    TaskObject task_from;
    TaskObject task_to;
};

}  // namespace types::trace