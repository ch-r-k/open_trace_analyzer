#include "export_puml.hpp"

namespace application::export_data::seq_diagram
{
Puml::Puml(const std::string& filename) : output_file(filename) {}

void Puml::addParticipant(std::list<task_types::TaskObject> task_objects)
{
    for (const auto& task : task_objects)
    {
        output_file << "participant " << task.getName() << "\n";
    }
}
void Puml::addMessage(std::string message, TaskObject from, TaskObject to)
{
    output_file << from.getName()  //
                << " -> "          //
                << to.getName()    //
                << " : "           //
                << message         //
                << "\n";
}

void Puml::addNote(TaskObject task, std::string note)
{
    output_file << "hnote over "   //
                << task.getName()  //
                << " : "           //
                << note            //
                << "\n";
}

void Puml::activate(TaskObject task_object)
{
    output_file << "activate "            //
                << task_object.getName()  //
                << "\n";
}

void Puml::deactivate(TaskObject task_object)
{
    output_file << "deactivate "          //
                << task_object.getName()  //
                << "\n";
}

void Puml::addTimestamp(std::uint64_t timestamp)
{
    // empty
}

}  // namespace application::export_data::seq_diagram