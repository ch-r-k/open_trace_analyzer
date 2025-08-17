#pragma once

#include <list>
#include <string>

#include "application/task_object/task_object.hpp"
//#include "3d_party/json/include/nlohmann/json.hpp"

namespace application::export_data::seq_diagram
{
using task_types::TaskObject;
class ISeqDiagram
{
   public:
    ~ISeqDiagram() = default;

    virtual void addParticipant(
        std::list<task_types::TaskObject> task_objects) = 0;
    virtual void addMessage(std::string message, TaskObject from,
                            TaskObject to) = 0;
    virtual void addNote(TaskObject task, std::string note) = 0;
    virtual void activate(task_types::TaskObject task_object) = 0;
    virtual void deactivate(task_types::TaskObject task_object) = 0;
};
}  // namespace application::export_data::seq_diagram