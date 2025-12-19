#pragma once

#include <cstdint>
#include <list>
#include "types/task_object/task_object.hpp"
#include "types/trace_entry/event_message/event_message.hpp"
#include "types/trace_entry/notes/note.hpp"
#include "types/trace_entry/state_machine/state_machine.hpp"
#include "types/trace_entry/task_switch/task_switch.hpp"
#include "types/trace_entry/trace_entry.hpp"

namespace import
{
class IImportObject;
class IImportTrace;
}  // namespace import

namespace export_data::seq_diagram
{
class ISeqDiagram;
}

namespace application
{
using export_data::seq_diagram::ISeqDiagram;
using import::IImportObject;
using import::IImportTrace;

using types::task::TaskObject;
using types::trace::EventMessage;
using types::trace::Note;
using types::trace::StateMachine;
using types::trace::TaskSwitch;
using types::trace::TraceEntry;

class App
{
   public:
    App(IImportObject& object_import,  //
        IImportTrace& trace_import,    //
        ISeqDiagram& seq_export,       //
        const double timestemp_scaling_factor);
    ~App() = default;

    void importData(void);
    void combineTraces(void);
    void process(void);
    void exportData(void);
    void execute(void);

   private:
    const double timestemp_scaling_factor;
    IImportObject& object_import;
    IImportTrace& trace_import;
    ISeqDiagram& seq_export;

    std::list<TaskObject> task_objects{};
    std::list<EventMessage> event_messages{};
    std::list<StateMachine> state_machine{};
    std::list<TaskSwitch> task_switches{};
    std::list<Note> notes{};
    std::list<TraceEntry*> trace_entries{};
};
}  // namespace application