#pragma once

#include <list>
#include "application/task_object/task_object.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/import/task_objects/import_object.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/trace_entry/state_machine/state_machine.hpp"
#include "application/trace_entry/task_switch/task_switch.hpp"

namespace application
{
class App
{
   public:
    App();
    ~App() = default;

    void execute(void);

   private:
    import::ImportObject qsp_import;
    import::ImportTrace qspy_import;
    std::list<task_types::TaskObject> task_objects{};
    std::list<trace_types::EventMessage> event_messages{};
    std::list<trace_types::StateMachine> state_machine{};
    std::list<trace_types::TaskSwitch> task_switches{};
    std::list<trace_types::TaskSwitch*> trace_entries{};
};
}  // namespace application