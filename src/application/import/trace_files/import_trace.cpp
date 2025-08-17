
#include <bits/c++config.h>
#include <cassert>
#include <cstdint>
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

void ImportTrace::get(
    [[maybe_unused]] std::list<TraceEntry>& event_message_list) const
{
    assert(false && "not implemented");
}

void ImportTrace::get(std::list<TaskSwitch>& task_switch_list) const
{
    std::ifstream in(file_name);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + file_name);
    }

    std::string line;
    // Regex to match: timestamp AO-Post Sdr=...,Obj=...,Evt<Sig=...>
    std::regex re(R"(^\s*(\d+)\s+(Sch-(Next|Idle))\s+Pri=(\d+)->(\d+))");
    std::size_t line_number{0};

    while (std::getline(in, line))
    {
        std::smatch match;
        if (std::regex_search(line, match, re))
        {
            uint64_t timestamp = std::stoull(match[1].str());
            std::uint32_t task_from_priority =
                static_cast<std::uint32_t>(std::stoul(match[4].str()));
            std::uint32_t task_to_priority =
                static_cast<std::uint32_t>(std::stoul(match[5].str()));

            const TaskObject& task_from = findTask(task_from_priority);
            const TaskObject& task_to = findTask(task_to_priority);

            task_switch_list.emplace_back(line_number, timestamp, task_from,
                                          task_to);
        }

        line_number++;
    }
}

void ImportTrace::get(std::list<EventMessage>& event_message_list)
{
    std::ifstream in(file_name);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + file_name);
    }

    std::string line;
    std::size_t line_number{0};

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

            event_message_list.emplace_back(line_number, timestamp, task_from,
                                            task_to, text);
        }

        line_number++;
    }
}

void ImportTrace::get(std::list<StateMachine>& state_list) const
{
    std::ifstream in(file_name);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + file_name);
    }

    std::string line;
    std::size_t line_number{0};
    // Regex to match: timestamp AO-Post Sdr=...,Obj=...,Evt<Sig=...>

    std::regex re(
        R"(^\s*(\d+)\s+===\>Tran\s+Obj=([^,]+),.*State=[^>]+->([^,]+))");

    while (std::getline(in, line))
    {
        std::smatch match;
        if (std::regex_search(line, match, re))
        {
            uint64_t timestamp = std::stoull(match[1].str());
            std::string task_from_name = match[2].str();
            std::string state_name = match[3].str();

            const TaskObject& task = findTask(task_from_name);

            state_list.emplace_back(line_number, timestamp, task, state_name);
        }

        line_number++;
    }
}

const TaskObject& ImportTrace::findTask(const std::string& name) const
{
    for (const auto& task : task_objects)
    {
        if (task.getID() == name)
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

const TaskObject& ImportTrace::findTask(const std::uint32_t& priority) const
{
    for (const auto& task : task_objects)
    {
        if (task.getPriority() == priority)
        {
            return task;
        }
    }

    for (const auto& task : task_objects)
    {
        if (task.getPriority() == 0)
        {
            return task;
        }
    }

    throw std::runtime_error("TaskObject not found for priority: ");
}
}  // namespace application::import