#pragma once

#include <cstddef>
#include <list>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "types/task_object/task_object.hpp"
#include "../i_export_sequence.hpp"

namespace export_data::seq_diagram
{
using Json = nlohmann::json;
using types::task::TaskObject;
class OpenTraceViewer : public ISeqDiagram
{
   public:
    OpenTraceViewer(const std::string& filename);
    ~OpenTraceViewer();

    void addParticipant(std::list<TaskObject> task_objects) override;
    void addMessage(std::string message, TaskObject from,
                    TaskObject to) override;
    void addNote(TaskObject task, std::string note) override;
    void activate(TaskObject task_object) override;
    void deactivate(TaskObject task_object) override;
    void addTimestamp(std::uint64_t timestamp) override;

    std::size_t getActiveTasks(void) const;
    std::vector<Json>& getMessages();
    const std::vector<std::vector<Json>>& getStates() const;
    std::vector<Json>& getTasks(void);

   private:
    std::ofstream output_file;

    std::unordered_map<std::string, uint64_t> activeTasks{};
    std::unordered_map<std::string, std::size_t> taskIndexMap{};
    std::vector<Json> json_tasks{};
    std::vector<Json> json_messages{};
    std::vector<std::vector<Json>> json_states{};
    std::uint64_t last_timestamp{0};
};
}  // namespace export_data::seq_diagram