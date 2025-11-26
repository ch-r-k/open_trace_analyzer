#include <cstdint>
#include <list>
#include <unordered_map>
#include "application/app.hpp"
#include "types/trace_entry/task_switch/task_switch.hpp"

namespace application::calculation
{

using types::trace::TaskSwitch;

class TaskTimingCalculator
{
   public:
    TaskTimingCalculator(const std::list<TaskSwitch>& tasks) : tasks{tasks} {}

    ~TaskTimingCalculator() = default;

    void process(uint64_t start_time,  //
                 uint64_t end_time)
    {
        const auto tasks_filtered = filterTasks(start_time, end_time);
        if (tasks_filtered.empty()) return;

        const TaskSwitch* prev = nullptr;

        for (const auto& e : tasks_filtered)
        {
            // Handle the first entry separately
            if (!prev)
            {
                auto running = e.getFrom();
                exec[running.getID()] += (e.getTimestamp());
            }
            else
            {
                auto dt = e.getTimestamp() - prev->getTimestamp();
                auto running = prev->getTo();  // task active before this event
                exec[running.getID()] += dt;
            }

            prev = &e;  // update for next iteration
        }

        auto last_running = prev->getTo();
        exec[last_running.getID()] += (end_time - prev->getTimestamp());
    }

    std::list<TaskSwitch> filterTasks(uint64_t start_time,  //
                                      uint64_t end_time)
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

    std::uint64_t get(const std::string& id) { return exec[id]; }

   private:
    std::unordered_map<std::string, uint64_t> exec;

    const std::list<TaskSwitch>& tasks;
    std::uint64_t start_time;
    std::uint64_t end_time;
};

}  // namespace application::calculation