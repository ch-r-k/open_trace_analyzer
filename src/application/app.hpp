#pragma once

#include <list>
#include "application/task_object/task_object.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/import/task_objects/import_object.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/trace_entry/state_machine/state_machine.hpp"
#include "application/trace_entry/task_switch/task_switch.hpp"
#include "application/trace_entry/trace_entry.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"

namespace application
{
class App
{
   public:
    App();
    ~App() = default;

    void importData(void);
    void combineTraces(void);
    void exportData(void);
    void execute(void);

   private:
    import::ImportObject object_import;
    import::ImportTrace qspy_import;
    export_data::seq_diagram::Puml puml_export;

    std::list<task_types::TaskObject> task_objects{};
    std::list<trace_types::EventMessage> event_messages{};
    std::list<trace_types::StateMachine> state_machine{};
    std::list<trace_types::TaskSwitch> task_switches{};
    std::list<trace_types::TraceEntry*> trace_entries{};
};
}  // namespace application