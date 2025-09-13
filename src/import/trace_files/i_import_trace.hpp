#pragma once

#include <cstdint>
#include <string>
#include <list>

#include "import/task_objects/i_import_object.hpp"
#include "application/trace_entry/trace_entry.hpp"
#include "application/trace_entry/task_switch/task_switch.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/trace_entry/state_machine/state_machine.hpp"

namespace import
{
using application::task_types::TaskObject;
using application::trace_types::EventMessage;
using application::trace_types::StateMachine;
using application::trace_types::TaskSwitch;
using application::trace_types::TraceEntry;

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