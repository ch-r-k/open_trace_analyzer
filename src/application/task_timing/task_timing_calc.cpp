#include "task_timing_calc.hpp"

namespace application::calculation
{

TaskTimingCalculator::TaskTimingCalculator(const std::list<TaskSwitch>& tasks)
    : tasks{tasks}
{
}

void TaskTimingCalculator::process(const uint64_t start_time,  //
                                   const uint64_t end_time)
{
    const auto tasks_filtered = filterTasks(start_time, end_time);
    if (tasks_filtered.empty()) return;

    const TaskSwitch* previous_task_switch = nullptr;

    for (const auto& task_switch : tasks_filtered)
    {
        // Handle the first entry separately
        if (!previous_task_switch)
        {
            auto running = task_switch.getFrom();
            execution_time[running.getID()] += (task_switch.getTimestamp());
        }
        else
        {
            auto dt = task_switch.getTimestamp() -
                      previous_task_switch->getTimestamp();
            auto running =
                previous_task_switch->getTo();  // task active before this event
            execution_time[running.getID()] += dt;
        }

        previous_task_switch = &task_switch;  // update for next iteration
    }

    auto last_running = previous_task_switch->getTo();
    execution_time[last_running.getID()] +=
        (end_time - previous_task_switch->getTimestamp());
}

std::list<TaskSwitch> TaskTimingCalculator::filterTasks(
    const uint64_t start_time,  //
    const uint64_t end_time)
{
    std::list<TaskSwitch> result;

    for (const auto& e : tasks)
    {
        if (e.getTimestamp() >= start_time && e.getTimestamp() <= end_time)
        {
            result.push_back(e);
        }
    }

    return result;
}

std::uint64_t TaskTimingCalculator::get(const std::string& id)
{
    return execution_time[id];
}

}  // namespace application::calculation