#include "task_object.hpp"
#include <cstdint>
#include <iostream>

namespace application::task_types
{
TaskObject::TaskObject(std::uint32_t priority, std::uint32_t id,
                       std::string_view name)
    : priority{priority}, id{id}, name{name}
{
}

std::ostream& operator<<(std::ostream& os, const TaskObject& p)
{
    os << "Name: " << p.name;
    return os;
}

}  // namespace application::task_types