#pragma once

#include <list>
#include <string>
#include <fstream>
#include "application/task_object/task_object.hpp"
#include "../i_export_sequence.hpp"

namespace application::export_data::seq_diagram
{
using task_types::TaskObject;
class Puml : public ISeqDiagram
{
   public:
    Puml(const std::string& filename);
    ~Puml() = default;

    void addParticipant(
        std::list<task_types::TaskObject> task_objects) override;
    void addMessage(std::string message, TaskObject from,
                    TaskObject to) override;
    void addNote(TaskObject task, std::string note) override;
    void activate(task_types::TaskObject task_object) override;
    void deactivate(task_types::TaskObject task_object) override;

   private:
    std::ofstream output_file;
};
}  // namespace application::export_data::seq_diagram