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
    ~IImportObject() = default;
    enum class FileConfig : std::uint16_t
    {
        QSPY_TXT = 0,
    };

    virtual void setConfig(FileConfig config) = 0;
    virtual void setFile(std::string file_name) = 0;
    virtual void getTaskObject(const std::list<TaskObject>& lst) = 0;
};
}  // namespace application::import