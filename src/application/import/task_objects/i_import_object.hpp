#pragma once

#include <cstdint>
#include <list>
#include <string>
#include "application/task_object/task_object.hpp"

namespace application::import
{
using task_types::TaskObject;

class IImportObject
{
   public:
    virtual ~IImportObject() = default;
    virtual void getTaskObject(std::list<TaskObject>& lst) = 0;
};
}  // namespace application::import