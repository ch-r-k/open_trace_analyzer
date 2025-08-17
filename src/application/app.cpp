#include "app.hpp"
#include <iostream>
#include "application/import/task_objects/i_import_object.hpp"
#include "application/import/trace_files/i_import_trace.hpp"
#include "application/export/sequence_diagram/i_export_sequence.hpp"

namespace application
{
App::App(IImportObject& object_import,  //
         IImportTrace& trace_import,    //
         ISeqDiagram& seq_export)
    : object_import{object_import},  //
      trace_import{trace_import},    //
      seq_export{seq_export}
{
}

void App::importData(void)
{
    object_import.getTaskObject(task_objects);

    // ad default object
    TaskObject task_object{100, "unknown", "unknown"};
    task_objects.emplace_back(task_object);

    trace_import.setTaskObjects(task_objects);
    trace_import.get(event_messages);
    trace_import.get(state_machine);
    trace_import.get(task_switches);
}

void App::combineTraces(void)
{
    for (auto& ts : task_switches)
    {
        trace_entries.push_back(&ts);
    }
    for (auto& ev : event_messages)
    {
        trace_entries.push_back(&ev);
    }
    for (auto& sm : state_machine)
    {
        trace_entries.push_back(&sm);
    }
}

void App::exportData(void)
{
    seq_export.addParticipant(task_objects);

    trace_entries.sort([](const TraceEntry* a, const TraceEntry* b) {
        return *a < *b;  // dereference to call operator<
    });

    for (const auto& element : trace_entries)
    {
        // auto task_switch = dynamic_cast<TaskSwitch*>(element);
        // if (task_switch)
        // {
        //     seq_export.deactivate(task_switch->getFrom());
        //     seq_export.activate(task_switch->getTo());
        // }

        auto state_machine = dynamic_cast<StateMachine*>(element);
        if (state_machine)
        {
            seq_export.addNote(state_machine->getTask(),
                               state_machine->getState());
        }

        auto event_message = dynamic_cast<EventMessage*>(element);
        if (event_message)
        {
            seq_export.addMessage(event_message->getText(),
                                  event_message->getFrom(),
                                  event_message->getTo());
        }
    }
}

}  // namespace application