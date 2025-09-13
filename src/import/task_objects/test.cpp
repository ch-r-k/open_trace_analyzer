#include <fstream>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "import_object.hpp"

using import::ImportObject;
using types::task::TaskObject;

class ImportObjectFileTest : public ::testing::Test
{
   protected:
    std::string test_filename = "test.json";

    void SetUp() override
    {
        std::ofstream out(test_filename);
        out << R"([
            {"priority": 1, "id": "T1", "name": "Task One"},
            {"priority": 2, "id": "T2", "name": "Task Two"}
        ])";
    }

    void TearDown() override { std::remove(test_filename.c_str()); }
};

TEST_F(ImportObjectFileTest, ParsesValidJsonIntoTaskObjects)
{
    ImportObject importer(test_filename);
    std::list<TaskObject> tasks;

    importer.getTaskObject(tasks);

    ASSERT_EQ(tasks.size(), 2u);

    auto it = tasks.begin();
    EXPECT_EQ(it->getPriority(), 1);
    EXPECT_EQ(it->getID(), "T1");
    EXPECT_EQ(it->getName(), "Task One");

    ++it;
    EXPECT_EQ(it->getPriority(), 2);
    EXPECT_EQ(it->getID(), "T2");
    EXPECT_EQ(it->getName(), "Task Two");
}

TEST_F(ImportObjectFileTest, ThrowsOnMalformedJson)
{
    std::ofstream out(test_filename);
    out << R"([{"priority": "oops", "id": "X", "name": "Broken"}])";

    out.close();

    ImportObject importer(test_filename);
    std::list<TaskObject> tasks;
    EXPECT_THROW(importer.getTaskObject(tasks), nlohmann::json::type_error);
}

TEST(ImportObjectTest, ThrowsIfFileDoesNotExist)
{
    EXPECT_THROW(import::ImportObject("nonexistent.json"), std::runtime_error);
}
