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

    auto json_entry = viewer->getJson()[0];
    EXPECT_EQ(json_entry["Task"], "task");
    EXPECT_EQ(json_entry["Start"], 100);
    EXPECT_EQ(json_entry["Finish"], 200);
}

TEST_F(OpenTraceViewerTest, DeactivateNonexistentTaskDoesNothing)
{
    TaskObject task{0, "task_missing", "task_missing"};

    viewer->addTimestamp(10);
    viewer->deactivate(task);
}

}  // namespace test