#include "task_object.hpp"
#include <cstdint>
#include <iostream>
#include <string>

namespace application::task_types
{
TaskObject::TaskObject(std::uint32_t priority, std::uint32_t id,
                       std::string name)
    : priority{priority}, id{id}, name{name}
{
}

std::string TaskObject::getName() const { return name; }

std::ostream& operator<<(std::ostream& os, const TaskObject& p)
{
    os << "Name: " << p.name;
    return os;
}

}  // namespace application::task_types