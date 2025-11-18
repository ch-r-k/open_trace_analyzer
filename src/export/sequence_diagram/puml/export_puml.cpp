#include "export_puml.hpp"

namespace export_data::seq_diagram
{
using types::task::TaskObject;

Puml::Puml(const std::string& filename) : output_file(filename)
{
    output_file << "@startuml \n";
}

Puml::~Puml()
{
    output_file << "@enduml \n";
    output_file.flush();
    output_file.close();
}

void Puml::addParticipant(std::list<TaskObject> task_objects)
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

void Puml::addState(TaskObject task, std::string note)
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

void Puml::addNote(std::string note)
{
    // intentional left empty
}

}  // namespace export_data::seq_diagram