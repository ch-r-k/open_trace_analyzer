#include "task_object.hpp"
#include <cstdint>
#include <iostream>
#include <string>

namespace types::task
{
TaskObject::TaskObject(std::uint32_t priority, std::string id, std::string name)
    : priority{priority}, id{id}, name{name}
{
}

std::string TaskObject::getName() const { return name; }
std::string TaskObject::getID() const { return id; }
std::uint32_t TaskObject::getPriority() const { return priority; }

std::ostream& operator<<(std::ostream& os, const TaskObject& p)
{
    os << p.name;
    return os;
}

}  // namespace types::task