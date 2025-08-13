#pragma once

#include <cstdint>
#include <string>

namespace application::task_types
{
class TaskObject
{
   public:
    TaskObject(std::uint32_t priority, std::uint32_t id, std::string name);
    ~TaskObject() = default;

    friend std::ostream& operator<<(std::ostream& os, const TaskObject& p);

    std::string getName() const;

   private:
    std::uint32_t priority;
    std::uint32_t id;
    std::string name;
};

}  // namespace application::task_types