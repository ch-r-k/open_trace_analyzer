#pragma once

#include <cstdint>
#include <list>
#include <string>
#include <fstream>
#include "application/task_object/task_object.hpp"
#include "../i_export_sequence.hpp"

namespace export_data::seq_diagram
{
using application::task_types::TaskObject;
class PumlTiming : public ISeqDiagram
{
   public:
    PumlTiming(const std::string& filename);
    ~PumlTiming() = default;

    void addParticipant(std::list<TaskObject> task_objects) override;
    void addMessage(std::string message, TaskObject from,
                    TaskObject to) override;
    void addNote(TaskObject task, std::string note) override;
    void activate(TaskObject task_object) override;
    void deactivate(TaskObject task_object) override;

   private:
    std::ofstream output_file;
    const std::string STATE_PREFIX{"_state"};
    const std::string ACTIVE_PREFIX{"_active"};

    void addTimestamp(std::uint64_t timestamp) override;
};
}  // namespace export_data::seq_diagram