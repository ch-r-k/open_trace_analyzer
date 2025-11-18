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
        output_json["tasks"] = json_tasks;
        output_json["states"] = json_states;
        output_json["messages"] = json_messages;
        output_json["notes"] = json_note;

        // Pretty-print with indentation for readability
        output_file << output_json.dump(4);

        output_file.close();
    }
}

void OpenTraceViewer::addParticipant(std::list<TaskObject> task_objects)
{
    for (const auto& task : task_objects)
    {
        if (taskIndexMap.find(task.getName()) == taskIndexMap.end())
        {
            taskIndexMap[task.getName()] = json_states.size();
            json_states.emplace_back();  // Create empty vector for this task
        }
    }
}

void OpenTraceViewer::addMessage(std::string message, TaskObject from,
                                 TaskObject to)
{
    Json entry = {{"From", from.getName()},
                  {"To", to.getName()},
                  {"Timestamp", last_timestamp},
                  {"Text", message}};

    json_messages.push_back(entry);
}

void OpenTraceViewer::addState(TaskObject task, std::string note)
{
    auto it = taskIndexMap.find(task.getName());
    if (it == taskIndexMap.end())
    {
        // If task wasn't added yet, create entry
        taskIndexMap[task.getName()] = json_states.size();
        json_states.emplace_back();
    }

    std::size_t index = taskIndexMap[task.getName()];
    Json state_entry = {
        {"Task", task.getName()}, {"time", last_timestamp}, {"State", note}};

    json_states[index].push_back(state_entry);
}

void OpenTraceViewer::addNote(std::string note)
{
    Json entry = {{"Timestamp", last_timestamp},  //
                  {"Text", note}};

    json_note.push_back(entry);
}

void OpenTraceViewer::activate(TaskObject task_object)
{
    activeTasks[task_object.getName()] = last_timestamp;
}
void OpenTraceViewer::deactivate(TaskObject task_object)
{
    auto active_task = activeTasks.find(task_object.getName());
    if (active_task != activeTasks.end())
    {
        // Build a completed JSON entry
        Json entry = {{"Task", task_object.getName()},
                      {"Start", active_task->second},
                      {"Finish", last_timestamp}};

        json_tasks.push_back(entry);

        // Remove from active list
        activeTasks.erase(active_task);
    }
    else
    {
    }
}

void OpenTraceViewer::addTimestamp(std::uint64_t timestamp)
{
    last_timestamp = timestamp;
}

std::size_t OpenTraceViewer::getActiveTasks(void) const
{
    return activeTasks.size();
}

std::vector<Json>& OpenTraceViewer::getTasks(void) { return json_tasks; }

const std::vector<std::vector<Json>>& OpenTraceViewer::getStates() const
{
    return json_states;
}

std::vector<Json>& OpenTraceViewer::getMessages() { return json_messages; }

}  // namespace export_data::seq_diagram