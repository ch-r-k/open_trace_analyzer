#pragma once

#include <cstdint>
#include <string_view>
#include "application/task_object/task_object.hpp"
#include "../trace_entry.hpp"

namespace application::trace_types
{
using task_types::TaskObject;

class EventMessage : public TraceEntry
{
   public:
    EventMessage(std::uint64_t timestamp, TaskObject& task_from,
                 TaskObject& task_to, std::string_view text);
    ~EventMessage() = default;

    friend std::ostream& operator<<(std::ostream& os, const EventMessage& p);

   private:
    TaskObject& task_from;
    TaskObject& task_to;
    std::string_view text;
};

}  // namespace application::trace_types