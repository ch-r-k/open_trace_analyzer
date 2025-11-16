#include <gtest/gtest.h>
#include "../open_trace_viewer.hpp"
#include "types/task_object/task_object.hpp"

namespace test
{

using export_data::seq_diagram::OpenTraceViewer;
using types::task::TaskObject;

class OpenTraceViewerTest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        viewer = std::make_unique<OpenTraceViewer>("./test.json");
    }

    std::unique_ptr<OpenTraceViewer> viewer;
};

TEST_F(OpenTraceViewerTest, DeactivateMovesTaskToCompletedTasks)
{
    TaskObject task{0, "task", "task"};

    viewer->addTimestamp(100);
    viewer->activate(task);
    viewer->addTimestamp(200);
    viewer->deactivate(task);

    auto json_entry = viewer->getTasks()[0];
    EXPECT_EQ(json_entry["Task"], "task");
    EXPECT_EQ(json_entry["Start"], 100);
    EXPECT_EQ(json_entry["Finish"], 200);
}

TEST_F(OpenTraceViewerTest, DeactivateNonexistentTaskDoesNothing)
{
    TaskObject task{0, "task_missing", "task_missing"};
    viewer->addTimestamp(10);
    viewer->deactivate(task);

    // Should NOT crash; json_tasks must remain empty
    EXPECT_TRUE(viewer->getTasks().empty());
}

TEST_F(OpenTraceViewerTest, AddStateCreatesStateEntry)
{
    TaskObject task{1, "worker", "worker"};

    viewer->addTimestamp(123);
    viewer->addState(task, "Initialized");

    auto &states = viewer->getStates();
    ASSERT_EQ(states.size(), 1);  // one participant/state list

    ASSERT_EQ(states[0].size(), 1);  // one state entry
    auto entry = states[0][0];

    EXPECT_EQ(entry["Task"], "worker");
    EXPECT_EQ(entry["time"], 123);
    EXPECT_EQ(entry["State"], "Initialized");
}

TEST_F(OpenTraceViewerTest, AddMessageCreatesMessageEntry)
{
    TaskObject from{1, "sender", "sender"};
    TaskObject to{2, "receiver", "receiver"};

    viewer->addTimestamp(555);
    viewer->addMessage("Hello", from, to);

    auto &messages = viewer->getMessages();
    ASSERT_EQ(messages.size(), 1);

    auto entry = messages[0];
    EXPECT_EQ(entry["From"], "sender");
    EXPECT_EQ(entry["To"], "receiver");
    EXPECT_EQ(entry["Timestamp"], 555);
    EXPECT_EQ(entry["Text"], "Hello");
}

}  // namespace test