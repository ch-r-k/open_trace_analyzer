#pragma once

#include <cstdint>
#include <string>
#include "application/task_object/task_object.hpp"
#include "../trace_entry.hpp"

namespace application::trace_types
{
using task_types::TaskObject;

class EventMessage : public TraceEntry
{
   public:
    EventMessage(std::uint64_t timestamp, const TaskObject& task_from,
                 const TaskObject& task_to, std::string text);
    ~EventMessage() = default;

    friend std::ostream& operator<<(std::ostream& os, const EventMessage& p);

   private:
    TaskObject task_from;
    TaskObject task_to;
    std::string text;
};

}  // namespace application::trace_types