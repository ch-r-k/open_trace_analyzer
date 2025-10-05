#include "export_puml_timing.hpp"
#include "types/task_object/task_object.hpp"

namespace export_data::seq_diagram
{
using types::task::TaskObject;

PumlTiming::PumlTiming(const std::string& filename) : output_file(filename)
{
    output_file << "@startuml \n";
}

PumlTiming::~PumlTiming()
{
    output_file << "@enduml \n";
    output_file.flush();
    output_file.close();
}

void PumlTiming::addParticipant(std::list<TaskObject> task_objects)
{
    for (const auto& task : task_objects)
    {
        output_file << "robust "                       //
                    << "\"" << task.getName() << "\""  //
                    << " as "                          //
                    << task.getName() << STATE_PREFIX  //
                    << "\n";

        output_file << "binary "                        //
                    << "\"" << task.getName() << "\""   //
                    << " as "                           //
                    << task.getName() << ACTIVE_PREFIX  //
                    << "\n";
    }
}
void PumlTiming::addMessage(std::string message, TaskObject from, TaskObject to)
{
    output_file << from.getName() << STATE_PREFIX  //
                << " -> "                          //
                << to.getName() << STATE_PREFIX    //
                << " : "                           //
                << message                         //
                << "\n";
}

void PumlTiming::addNote(TaskObject task, std::string note)
{
    output_file << task.getName() << STATE_PREFIX  //
                << " is "                          //
                << note                            //
                << "\n";
}

void PumlTiming::activate(TaskObject task_object)
{
    output_file << task_object.getName() << ACTIVE_PREFIX  //
                << " is "                                  //
                << " high "                                //
                << "\n";
}
void PumlTiming::deactivate(TaskObject task_object)
{
    output_file << task_object.getName() << ACTIVE_PREFIX  //
                << " is "                                  //
                << " low "                                 //
                << "\n";
}

void PumlTiming::addTimestamp(std::uint64_t timestamp)
{
    output_file << "@"        //
                << timestamp  //
                << "\n";
}

}  // namespace export_data::seq_diagram