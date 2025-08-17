#pragma once

#include <bits/stdint-uintn.h>
#include <cstdint>
#include <string>
#include <list>
#include <fstream>

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

class ImportTrace : public IImportTrace
{
   public:
    ImportTrace(const std::string& filename);
    ~ImportTrace() = default;
    enum class FileConfig : std::uint16_t
    {
        QSPY_TXT = 0,
    };

    void setConfig(FileConfig config);
    void setTaskObjects(const std::list<TaskObject>& task_objects) override;
    void get(std::list<TraceEntry>& lst) override;
    void get(std::list<TaskSwitch>& lst) override;
    void get(std::list<EventMessage>& lst) override;
    void get(std::list<StateMachine>& lst) override;

   private:
    std::ifstream input_file;
    const std::list<TaskObject>* task_objects{nullptr};

    const TaskObject& findTask(const std::string& name) const;
    const TaskObject& findTask(const std::uint32_t& priority) const;
};
}  // namespace application::import