#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include "types/task_object/task_object.hpp"
#include "../trace_entry.hpp"

namespace types::trace
{
using types::task::TaskObject;

class EventMessage : public TraceEntry
{
   public:
    EventMessage(const size_t line_number,       //
                 const std::uint64_t timestamp,  //
                 const TaskObject& task_from,    //
                 const TaskObject& task_to,      //
                 std::string text);
    ~EventMessage() = default;

    TaskObject getFrom();
    TaskObject getTo();
    std::string getText();

    friend std::ostream& operator<<(std::ostream& os, const EventMessage& p);

   private:
    TaskObject task_from;
    TaskObject task_to;
    std::string text;
};

}  // namespace types::trace