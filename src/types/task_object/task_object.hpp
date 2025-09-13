#pragma once

#include <cstdint>
#include <string>

namespace types::task
{
class TaskObject
{
   public:
    TaskObject(std::uint32_t priority, std::string id, std::string name);
    ~TaskObject() = default;

    friend std::ostream& operator<<(std::ostream& os, const TaskObject& p);

    std::string getName() const;
    std::string getID() const;
    std::uint32_t getPriority() const;

   private:
    std::uint32_t priority;
    std::string id;
    std::string name;
};

}  // namespace types::task