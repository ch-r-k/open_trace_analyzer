#pragma once

#include <cstdint>
#include <string>
#include <list>

#include "i_import_trace.hpp"
#include "application/trace_entry/trace_entry.hpp"
#include "application/trace_entry/task_switch/task_switch.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/trace_entry/state_machine/state_machine.hpp"
#include "application/task_object/task_object.hpp"

namespace application::import
{
using task_types::TaskObject;
using trace_types::EventMessage;
using trace_types::StateMachine;
using trace_types::TaskSwitch;
using trace_types::TraceEntry;

class ImportTrace
{
   public:
    ImportTrace(const std::list<TaskObject>& task_objects);
    ~ImportTrace() = default;
    enum class FileConfig : std::uint16_t
    {
        QSPY_TXT = 0,
    };

    void setConfig(FileConfig config);
    void setFile(std::string file_name);
    void get(std::list<TraceEntry>& lst) const;
    void get(std::list<TaskSwitch>& lst) const;
    void get(std::list<EventMessage>& lst);
    void get(std::list<StateMachine>& lst) const;

   private:
    std::string file_name;
    const std::list<TaskObject>& task_objects;

    const TaskObject& findTask(const std::string& name) const;
};
}  // namespace application::import