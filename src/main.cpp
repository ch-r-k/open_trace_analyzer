#include <iostream>
#include "application/task_object/task_object.hpp"
#include "application/trace_entry/event_message/event_message.hpp"
#include "application/trace_entry/state_machine/state_machine.hpp"
#include "application/trace_entry/task_switch/task_switch.hpp"

using application::task_types::TaskObject;
using application::trace_types::EventMessage;
using application::trace_types::StateMachine;
using application::trace_types::TaskSwitch;

int main(void)
{
    std::cout << "Task Objects:\n";
    TaskObject ao1{0, 0, "Active Object 1"};
    TaskObject ao2{1, 1, "Active Object 2"};
    std::cout << ao1 << "\n";
    std::cout << ao2 << "\n";

    std::cout << "Task Switches:\n";
    TaskSwitch task_switch_1{0, ao1, ao2};
    TaskSwitch task_switch_2{10, ao2, ao1};

    std::cout << task_switch_1 << "\n";
    std::cout << task_switch_2 << "\n";

    std::cout << "Task Messages:\n";
    EventMessage event_message_1{0, ao1, ao2, "TEST1"};
    EventMessage event_message_2{0, ao2, ao1, "TEST2"};

    std::cout << event_message_1 << "\n";
    std::cout << event_message_2 << "\n";

    std::cout << "State Machine:\n";
    StateMachine state_machine_1{0, ao1, "TEST1"};
    StateMachine state_machine_2{0, ao2, "TEST2"};

    std::cout << state_machine_1 << "\n";
    std::cout << state_machine_2 << "\n";

    std::cout << "Hello World\n";
    return 0;
}