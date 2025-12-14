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
    TaskTimingCalculator(const std::list<TaskSwitch>& tasks);
    ~TaskTimingCalculator() = default;

    void process(const uint64_t start_time,  //
                 const uint64_t end_time);

    std::list<TaskSwitch> filterTasks(const uint64_t start_time,  //
                                      const uint64_t end_time);

    std::uint64_t get(const std::string& id);

   private:
    std::unordered_map<std::string, uint64_t> execution_time{};

    const std::list<TaskSwitch>& tasks;
    std::uint64_t start_time;
    std::uint64_t end_time;
};

}  // namespace application::calculation