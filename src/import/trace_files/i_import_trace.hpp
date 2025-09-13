#pragma once

#include <cstdint>
#include <string>
#include <list>

#include "import/task_objects/i_import_object.hpp"
#include "types/trace_entry/trace_entry.hpp"
#include "types/trace_entry/task_switch/task_switch.hpp"
#include "types/trace_entry/event_message/event_message.hpp"
#include "types/trace_entry/state_machine/state_machine.hpp"
#include "types/task_object/task_object.hpp"

namespace import
{
using types::task::TaskObject;
using types::trace::EventMessage;
using types::trace::StateMachine;
using types::trace::TaskSwitch;
using types::trace::TraceEntry;

class IImportTrace
{
   public:
    virtual ~IImportTrace() = default;

    virtual void setTaskObjects(const std::list<TaskObject>& task_objects) = 0;
    virtual void get(std::list<TraceEntry>& lst) = 0;
    virtual void get(std::list<TaskSwitch>& lst) = 0;
    virtual void get(std::list<EventMessage>& lst) = 0;
    virtual void get(std::list<StateMachine>& lst) = 0;
};
}  // namespace import