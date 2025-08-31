#pragma once

#include <cstdint>
#include <list>
#include "application/task_object/task_object.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/trace_entry/state_machine/state_machine.hpp"
#include "application/trace_entry/task_switch/task_switch.hpp"
#include "application/trace_entry/trace_entry.hpp"

namespace application::import
{
class IImportObject;
class IImportTrace;
}  // namespace application::import

namespace application::export_data::seq_diagram
{
class ISeqDiagram;
}

namespace application
{
using export_data::seq_diagram::ISeqDiagram;
using import::IImportObject;
using import::IImportTrace;

using task_types::TaskObject;
using trace_types::EventMessage;
using trace_types::StateMachine;
using trace_types::TaskSwitch;
using trace_types::TraceEntry;

class App
{
   public:
    App(IImportObject& object_import,  //
        IImportTrace& trace_import,    //
        ISeqDiagram& seq_export);
    ~App() = default;

    void importData(void);
    void combineTraces(void);
    void exportData(void);
    void execute(void);

   private:
    IImportObject& object_import;
    IImportTrace& trace_import;
    ISeqDiagram& seq_export;

    std::list<TaskObject> task_objects{};
    std::list<EventMessage> event_messages{};
    std::list<StateMachine> state_machine{};
    std::list<TaskSwitch> task_switches{};
    std::list<TraceEntry*> trace_entries{};
};
}  // namespace application