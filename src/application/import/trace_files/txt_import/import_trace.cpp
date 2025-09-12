
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
ImportTrace::ImportTrace(const std::string& filename,
                         const EventMessageConfig event_message_config,
                         const StateMachineConfig state_machine_config,
                         const TaskSwitchConfig task_switch_config)
    : input_file{filename},                        //
      event_message_config{event_message_config},  //
      state_machine_config{state_machine_config},  //
      task_switch_config{task_switch_config}
{
    if (!input_file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

void ImportTrace::setTaskObjects(const std::list<TaskObject>& task_objects)
{
    this->task_objects = &task_objects;
}

void ImportTrace::get(
    [[maybe_unused]] std::list<TraceEntry>& event_message_list)
{
    throw std::runtime_error("Not Implemented");
}

void ImportTrace::get(std::list<TaskSwitch>& task_switch_list)
{
    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    std::string line;
    // Regex to match: timestamp AO-Post Sdr=...,Obj=...,Evt<Sig=...>
    std::regex re(R"(^\s*(\d+)\s+(Sch-(Next|Idle))\s+Pri=(\d+)->(\d+))");
    std::size_t line_number{0};

    while (std::getline(input_file, line))
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
    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    std::string line;
    std::size_t line_number{0};

    // Regex to match: timestamp AO-Post Sdr=...,Obj=...,Evt<Sig=...>
    std::regex re(
        R"(^\s*(\d+).*AO-Post.*Sdr=([^,]+),Obj=([^,]+).*Sig=([^,>]+))");

    while (std::getline(input_file, line))
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

void ImportTrace::get(std::list<StateMachine>& state_list)
{
    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    std::string line;
    std::size_t line_number{0};
    // Regex to match: timestamp AO-Post Sdr=...,Obj=...,Evt<Sig=...>

    std::regex re(
        R"(^\s*(\d+)\s+===\>Tran\s+Obj=([^,]+),.*State=[^>]+->([^,]+))");

    while (std::getline(input_file, line))
    {
        std::smatch match;
        if (std::regex_search(line, match, re))
        {
            uint64_t timestamp = std::stoull(match[1].str());
            std::string task_name = match[2].str();
            std::string state_name = match[3].str();

            const TaskObject& task = findTask(task_name);

            state_list.emplace_back(line_number, timestamp, task, state_name);
        }

        line_number++;
    }
}

const TaskObject& ImportTrace::findTask(const std::string& name) const
{
    if (task_objects == nullptr)
    {
        throw std::runtime_error("Task Object not set");
    }
    for (const auto& task : *task_objects)
    {
        if (task.getID() == name)
        {
            return task;
        }
    }

    for (const auto& task : *task_objects)
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
    if (task_objects == nullptr)
    {
        throw std::runtime_error("Task Object not set");
    }
    for (const auto& task : *task_objects)
    {
        if (task.getPriority() == priority)
        {
            return task;
        }
    }

    for (const auto& task : *task_objects)
    {
        if (task.getPriority() == 0)
        {
            return task;
        }
    }

    throw std::runtime_error("TaskObject not found for priority: ");
}
}  // namespace application::import