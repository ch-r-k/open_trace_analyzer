#include <gtest/gtest.h>
#include "task_object.hpp"
#include <cstdint>
#include <string>

using application::task_types::TaskObject;

// Define a parameter struct
struct TaskParams
{
    std::uint32_t priority;
    std::string id;
    std::string name;
};

// Define parameterized test fixture
class TaskObjectParamTest : public ::testing::TestWithParam<TaskParams>
{
};

// The actual test
TEST_P(TaskObjectParamTest, Import)
{
    const auto& p = GetParam();

    TaskObject task_object{p.priority, p.id, p.name};

    EXPECT_EQ(task_object.getPriority(), p.priority);
    EXPECT_EQ(task_object.getID(), p.id);
    EXPECT_EQ(task_object.getName(), p.name);
}

// Instantiate test cases with multiple parameter sets
INSTANTIATE_TEST_SUITE_P(TaskObjectTests, TaskObjectParamTest,
                         ::testing::Values(  //
                             TaskParams{0, "ID", "ID"},
                             TaskParams{5, "T123", "MyTask"},
                             TaskParams{10, "JobX", "ProcessingJob"}));
