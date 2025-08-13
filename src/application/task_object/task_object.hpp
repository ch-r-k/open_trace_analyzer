#pragma once

#include <cstdint>
#include <string_view>

namespace application::task_types
{
class TaskObject
{
   public:
    TaskObject(std::uint32_t priority, std::uint32_t id, std::string_view name);
    ~TaskObject() = default;

    friend std::ostream& operator<<(std::ostream& os, const TaskObject& p);

   private:
    std::uint32_t priority;
    std::uint32_t id;
    std::string_view name;
};

}  // namespace application::task_types