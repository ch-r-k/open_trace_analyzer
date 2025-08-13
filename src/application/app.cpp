#include "app.hpp"
#include <iostream>

namespace application
{
void App::execute(void)
{
    qsp_import.setFile(std::string{"test/input_files/qspy_ao.json"});
    qsp_import.getTaskObject(task_objects);

    for (const auto element : task_objects)
    {
        std::cout << element << "\n";
    }
}
}  // namespace application