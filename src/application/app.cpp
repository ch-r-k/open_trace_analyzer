#include "app.hpp"
#include <iostream>

namespace application
{
App::App() : qspy_import(task_objects) {}

void App::execute(void)
{
    qsp_import.setFile(std::string{"test/input_files/qspy_ao.json"});
    qsp_import.getTaskObject(task_objects);

    // ad default object
    import::TaskObject task_object{100, "unknown", "unknown"};

    task_objects.emplace_back(task_object);

    for (const auto element : task_objects)
    {
        std::cout << element << "\n";
    }

    qspy_import.setFile(std::string{"test/input_files/qpsy.txt"});
    qspy_import.get(event_messages);

    for (const auto element : event_messages)
    {
        std::cout << element << "\n";
    }

    qspy_import.get(state_machine);

    for (const auto element : state_machine)
    {
        std::cout << element << "\n";
    }
}
}  // namespace application