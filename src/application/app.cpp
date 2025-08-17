#include "app.hpp"
#include <iostream>

namespace application
{
App::App() : qspy_import(task_objects) {}

void App::importData(void)
{
    qsp_import.setFile(std::string{"test/input_files/qspy_ao.json"});
    qsp_import.getTaskObject(task_objects);

    // ad default object
    import::TaskObject task_object{100, "unknown", "unknown"};

    task_objects.emplace_back(task_object);

    for (const auto& element : task_objects)
    {
        std::cout << element << "\n";
    }

    qspy_import.setFile(std::string{"test/input_files/qpsy.txt"});
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
}  // namespace application