#pragma once

#include <cstdint>
#include <list>
#include <string>

#include "application/task_object/task_object.hpp"
//#include "3d_party/json/include/nlohmann/json.hpp"

namespace export_data::seq_diagram
{
using application::task_types::TaskObject;
class ISeqDiagram
{
   public:
    virtual ~ISeqDiagram() = default;

    virtual void addParticipant(std::list<TaskObject> task_objects) = 0;
    virtual void addMessage(std::string message, TaskObject from,
                            TaskObject to) = 0;
    virtual void addNote(TaskObject task, std::string note) = 0;
    virtual void activate(TaskObject task_object) = 0;
    virtual void deactivate(TaskObject task_object) = 0;
    virtual void addTimestamp(std::uint64_t) = 0;
};
}  // namespace export_data::seq_diagram