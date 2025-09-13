#pragma once

#include <cstdint>
#include <list>
#include <string>
#include "types/task_object/task_object.hpp"

namespace import
{
using types::task::TaskObject;

class IImportObject
{
   public:
    virtual ~IImportObject() = default;
    virtual void getTaskObject(std::list<TaskObject>& lst) = 0;
};
}  // namespace import