#pragma once

#include <list>
#include "application/task_object/task_object.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/import/task_objects/import_object.hpp"

namespace application
{
class App
{
   public:
    App() = default;
    ~App() = default;

    void execute(void);

   private:
    import::ImportObject qsp_import;
    std::list<task_types::TaskObject> task_objects{};
    std::list<trace_types::EventMessage> event_messages{};
};
}  // namespace application