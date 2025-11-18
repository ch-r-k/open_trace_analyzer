#pragma once

#include <bits/stdint-uintn.h>
#include <cstdint>
#include <string>
#include <list>
#include <fstream>

#include "../i_import_trace.hpp"
#include "types/trace_entry/trace_entry.hpp"
#include "types/trace_entry/task_switch/task_switch.hpp"
#include "types/trace_entry/event_message/event_message.hpp"
#include "types/trace_entry/state_machine/state_machine.hpp"
#include "types/task_object/task_object.hpp"
#include "txt_config/state_machine.hpp"
#include "txt_config/task_switch.hpp"
#include "txt_config/event_message.hpp"
#include "txt_config/note.hpp"

namespace import
{
using types::task::TaskObject;
using types::trace::EventMessage;
using types::trace::StateMachine;
using types::trace::TaskSwitch;
using types::trace::TraceEntry;

using StateMachineConfig = txt_config::StateMachine;
using TaskSwitchConfig = txt_config::TaskSwitch;
using EventMessageConfig = txt_config::EventMessage;
using NoteConfig = txt_config::Note;

class ImportTrace : public IImportTrace
{
   public:
    ImportTrace(const std::string& filename,
                const EventMessageConfig event_message_config,
                const StateMachineConfig state_machine_config,
                const TaskSwitchConfig task_switch_config,
                const NoteConfig note_config);

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
    void get(std::list<Note>& lst) override;

   private:
    std::ifstream input_file;
    const std::list<TaskObject>* task_objects{nullptr};

    const TaskObject& findTask(const std::string& name) const;
    const TaskObject& findTask(const std::uint32_t& priority) const;

    EventMessageConfig event_message_config;
    StateMachineConfig state_machine_config;
    TaskSwitchConfig task_switch_config;
    NoteConfig note_config;
};
}  // namespace import