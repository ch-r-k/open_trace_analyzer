#include "open_trace_viewer.hpp"

namespace export_data::seq_diagram
{
OpenTraceViewer::OpenTraceViewer(const std::string& filename)
    : output_file(filename)
{
}

OpenTraceViewer::~OpenTraceViewer()
{
    if (output_file.is_open())
    {
        // Wrap completed tasks in a top-level JSON object
        Json output_json;
        output_json["Tasks"] = completed_tasks;
        output_json["Messages"] = messages;

        // Pretty-print with indentation for readability
        output_file << output_json.dump(4);

        output_file.close();
    }
}

void OpenTraceViewer::addParticipant(std::list<TaskObject> task_objects)
{
    for (const auto& task : task_objects)
    {
    }
}
void OpenTraceViewer::addMessage(std::string message, TaskObject from,
                                 TaskObject to)
{
    Json entry = {
        {"Timestamp", last_timestamp},  //
        {"From", from.getName()},       //
        {"To", to.getName()},           //
        {"Text", message}               //
    };

    messages.push_back(entry);
}

void OpenTraceViewer::addNote(TaskObject task, std::string note) {}

void OpenTraceViewer::activate(TaskObject task_object)
{
    tasks[task_object.getName()] = last_timestamp;
}
void OpenTraceViewer::deactivate(TaskObject task_object)
{
    auto active_task = tasks.find(task_object.getName());
    if (active_task != tasks.end())
    {
        // Build a completed JSON entry
        Json entry = {{"Task", task_object.getName()},
                      {"Start", active_task->second},
                      {"Finish", last_timestamp}};

        completed_tasks.push_back(entry);

        // Remove from active list
        tasks.erase(active_task);
    }
    else
    {
    }
}

void OpenTraceViewer::addTimestamp(std::uint64_t timestamp)
{
    last_timestamp = timestamp;
}

std::size_t OpenTraceViewer::getActiveTasks(void) const { return tasks.size(); }

std::vector<Json>& OpenTraceViewer::getJson(void) { return completed_tasks; }

}  // namespace export_data::seq_diagram