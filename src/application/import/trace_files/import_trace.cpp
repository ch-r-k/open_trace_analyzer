
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>

#include "application/trace_entry/event_message/event_message.hpp"
#include "import_trace.hpp"

namespace application::import
{
ImportTrace::ImportTrace(const std::list<TaskObject>& task_objects)
    : task_objects{task_objects}
{
}

void ImportTrace::setFile(std::string file_name)
{
    this->file_name = file_name;
}

void ImportTrace::get(std::list<TraceEntry>& event_message_list) const
{
    assert(false && "not implemented");
}

void ImportTrace::get(std::list<TaskSwitch>& event_message_list) const
{
    assert(false && "not implemented");
}

void ImportTrace::get(std::list<EventMessage>& event_message_list)
{
    std::ifstream in(file_name);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + file_name);
    }

    std::string line;
    // Regex to match: timestamp AO-Post Sdr=...,Obj=...,Evt<Sig=...>
    std::regex re(
        R"(^\s*(\d+).*AO-Post.*Sdr=([^,]+),Obj=([^,]+).*Sig=([^,>]+))");

    while (std::getline(in, line))
    {
        std::smatch match;
        if (std::regex_search(line, match, re))
        {
            uint64_t timestamp = std::stoull(match[1].str());
            std::string task_from_name = match[2].str();
            std::string task_to_name = match[3].str();
            std::string text = match[4].str();

            const TaskObject& task_from = findTask(task_from_name);
            const TaskObject& task_to = findTask(task_to_name);

            event_message_list.emplace_back(timestamp, task_from, task_to,
                                            text);
        }
    }
}

void ImportTrace::get(std::list<StateMachine>& event_message_list) const
{
    assert(false && "not implemented");
}

const TaskObject& ImportTrace::findTask(const std::string& name) const
{
    for (const auto& task : task_objects)
    {
        if (task.getName() == name)
        {
            return task;
        }
    }

    for (const auto& task : task_objects)
    {
        if (task.getName() == "unknown")
        {
            return task;
        }
    }

    throw std::runtime_error("TaskObject not found for name: " + name);
}
}  // namespace application::import