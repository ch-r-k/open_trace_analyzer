#pragma once

#include <cstdint>
#include <string>
#include <list>

#include "application/trace_entry/trace_entry.hpp"
#include "application/trace_entry/task_switch/task_switch.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/trace_entry/state_machine/state_machine.hpp"

namespace application::import
{
using trace_types::EventMessage;
using trace_types::StateMachine;
using trace_types::TaskSwitch;
using trace_types::TraceEntry;

class IImportTrace
{
   public:
    ~IImportTrace() = default;
    enum class FileConfig : std::uint16_t
    {
        QSPY_TXT = 0,
    };

    virtual void setConfig(FileConfig config) = 0;
    virtual void setFile(std::string file_name) = 0;
    virtual void get(const std::list<TraceEntry>& lst) = 0;
    virtual void get(const std::list<TaskSwitch>& lst) = 0;
    virtual void get(const std::list<EventMessage>& lst) = 0;
    virtual void get(const std::list<StateMachine>& lst) = 0;
};
}  // namespace application::import