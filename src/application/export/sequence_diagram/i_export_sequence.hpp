#pragma once

#include <list>
#include "application/task_object/task_object.hpp"
//#include "3d_party/json/include/nlohmann/json.hpp"

#include <string>
namespace application::export_data::seq_diagram
{
class IExportSeqDiagram
{
   public:
    ~IExportSeqDiagram() = default;

    void addParticipant(std::list<task_types::TaskObject> task_objects);
    void addMessage(std::string message);
    void addNote(std::string message);
    void activate(task_types::TaskObject task_object);
    void deactivate(task_types::TaskObject task_object);
};
}  // namespace application::export_data::seq_diagram