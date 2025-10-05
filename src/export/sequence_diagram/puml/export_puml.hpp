#pragma once

#include <list>
#include <string>
#include <fstream>
#include "types/task_object/task_object.hpp"
#include "../i_export_sequence.hpp"

namespace export_data::seq_diagram
{
using types::task::TaskObject;
class Puml : public ISeqDiagram
{
   public:
    Puml(const std::string& filename);
    ~Puml();

    void addParticipant(std::list<TaskObject> task_objects) override;
    void addMessage(std::string message, TaskObject from,
                    TaskObject to) override;
    void addNote(TaskObject task, std::string note) override;
    void activate(TaskObject task_object) override;
    void deactivate(TaskObject task_object) override;

   private:
    std::ofstream output_file;
    void addTimestamp(std::uint64_t timestamp) override;
};
}  // namespace export_data::seq_diagram