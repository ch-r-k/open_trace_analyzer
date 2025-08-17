#include "app.hpp"
#include <iostream>

namespace application
{
App::App()
    : object_import{"test/input_files/qspy_ao.json"},          //
      qspy_import{task_objects, "test/input_files/qpsy.txt"},  //
      puml_export{"test/export_file.puml"}
{
}

void App::importData(void)
{
    object_import.getTaskObject(task_objects);

    // ad default object
    import::TaskObject task_object{100, "unknown", "unknown"};

    task_objects.emplace_back(task_object);

    for (const auto& element : task_objects)
    {
        std::cout << element << "\n";
    }

    qspy_import.get(event_messages);

    for (const auto& element : event_messages)
    {
        std::cout << element << "\n";
    }

    qspy_import.get(state_machine);

    for (const auto& element : state_machine)
    {
        std::cout << element << "\n";
    }

    qspy_import.get(task_switches);

    for (const auto& element : task_switches)
    {
        std::cout << element << "\n";
    }
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

    for (const auto& element : trace_entries)
    {
        std::cout << element << "\n";
    }
}

void App::exportData(void)
{
    puml_export.addParticipant(task_objects);

    trace_entries.sort(
        [](const trace_types::TraceEntry* a, const trace_types::TraceEntry* b) {
            return *a < *b;  // dereference to call operator<
        });

    for (const auto& element : trace_entries)
    {
        auto task_switch = dynamic_cast<trace_types::TaskSwitch*>(element);
        if (task_switch)
        {
            puml_export.deactivate(task_switch->getFrom());
            puml_export.activate(task_switch->getTo());
        }

        auto state_machine = dynamic_cast<trace_types::StateMachine*>(element);
        if (state_machine)
        {
            puml_export.addNote(state_machine->getTask(),
                                state_machine->getState());
        }

        auto event_message = dynamic_cast<trace_types::EventMessage*>(element);
        if (event_message)
        {
            puml_export.addMessage(event_message->getText(),
                                   event_message->getFrom(),
                                   event_message->getTo());
        }
    }
}

}  // namespace application