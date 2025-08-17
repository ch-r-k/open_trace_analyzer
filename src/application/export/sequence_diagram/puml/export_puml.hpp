#pragma once

#include <list>
#include <string>
#include <fstream>
#include "application/task_object/task_object.hpp"

namespace application::export_data::seq_diagram
{
using task_types::TaskObject;
class Puml
{
   public:
    Puml(const std::string& filename) : output_file(filename) {}
    ~Puml() = default;

    void addParticipant(std::list<task_types::TaskObject> task_objects);
    void addMessage(std::string message, TaskObject from, TaskObject to);
    void addNote(TaskObject task, std::string note);
    void activate(task_types::TaskObject task_object);
    void deactivate(task_types::TaskObject task_object);

   private:
    std::ofstream output_file;
};
}  // namespace application::export_data::seq_diagram