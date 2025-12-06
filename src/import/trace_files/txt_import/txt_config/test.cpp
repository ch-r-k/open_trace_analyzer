#include <gtest/gtest.h>
#include "txt_config.hpp"
#include "note.hpp"
#include "state_machine.hpp"
#include "task_switch.hpp"
#include "event_message.hpp"
#include "txt_config_exception.hpp"
#include <nlohmann/json.hpp>

namespace test
{

using namespace import::txt_config;
using Json = nlohmann::json;

// -------------------------------------------------------------
// TxtConfig Base Tests
// -------------------------------------------------------------

TEST(TxtConfig, ConstructFromJsonValid)
{
    Json json = {{"regex", "^(.*)$"},
                 {"groups",
                  {{{"index", 0},
                    {"name", "timestamp"},
                    {"description", "timestamp"}}}}};

    TxtConfig cfg(json);

    EXPECT_EQ(cfg.getRegex(), "^(.*)$");
    EXPECT_EQ(cfg.getTimestampPos(), 0);
}

TEST(TxtConfig, MissingRegexThrows)
{
    Json json = {{"groups",
                  {{{"index", 0},
                    {"name", "timestamp"},
                    {"description", "timestamp"}}}}};

    EXPECT_THROW(TxtConfig cfg(json), TxtImportException);
}

TEST(TxtConfig, MissingGroupsThrows)
{
    Json json = {{"regex", "x+"}};

    EXPECT_THROW(TxtConfig cfg(json), TxtImportException);
}

// -------------------------------------------------------------
// Note Tests
// -------------------------------------------------------------

TEST(Note, ConstructFromJsonValid)
{
    Json json = {
        {"regex", "note_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 1}, {"name", "text"}, {"description", "note text"}}}}};

    Note note(json);

    EXPECT_EQ(note.getRegex(), "note_regex");
    EXPECT_EQ(note.getTimestampPos(), 0);
    EXPECT_EQ(note.getTextPos(), 1);
}

TEST(Note, MissingTextGroupThrows)
{
    Json json = {{"regex", "note_regex"},
                 {"groups",
                  {{{"index", 0},
                    {"name", "timestamp"},
                    {"description", "timestamp"}}}}};

    EXPECT_THROW(Note note(json), TxtImportException);
}

// -------------------------------------------------------------
// StateMachine Tests
// -------------------------------------------------------------

TEST(StateMachine, ConstructFromJsonValid)
{
    Json json = {
        {"regex", "sm_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 1}, {"name", "task"}, {"description", "task"}},
          {{"index", 2}, {"name", "state_name"}, {"description", "state"}}}}};

    StateMachine sm(json);

    EXPECT_EQ(sm.getTaskPos(), 1);
    EXPECT_EQ(sm.getStatePos(), 2);
}

TEST(StateMachine, MissingTaskThrows)
{
    Json json = {
        {"regex", "sm_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 2}, {"name", "state_name"}, {"description", "state"}}}}};

    EXPECT_THROW(StateMachine sm(json), TxtImportException);
}

TEST(StateMachine, MissingStateThrows)
{
    Json json = {
        {"regex", "sm_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 1}, {"name", "task"}, {"description", "task"}}}}};

    EXPECT_THROW(StateMachine sm(json), TxtImportException);
}

// -------------------------------------------------------------
// TaskSwitch Tests
// -------------------------------------------------------------

TEST(TaskSwitch, ConstructFromJsonValid)
{
    Json json = {
        {"regex", "switch_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 1}, {"name", "task_from"}, {"description", "from"}},
          {{"index", 2}, {"name", "task_to"}, {"description", "to"}}}}};

    TaskSwitch ts(json);

    EXPECT_EQ(ts.getFromPos(), 1);
    EXPECT_EQ(ts.getToPos(), 2);
}

TEST(TaskSwitch, MissingFromThrows)
{
    Json json = {
        {"regex", "switch_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 2}, {"name", "task_to"}, {"description", "to"}}}}};

    EXPECT_THROW(TaskSwitch ts(json), TxtImportException);
}

TEST(TaskSwitch, MissingToThrows)
{
    Json json = {
        {"regex", "switch_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 1}, {"name", "task_from"}, {"description", "from"}}}}};

    EXPECT_THROW(TaskSwitch ts(json), TxtImportException);
}

// -------------------------------------------------------------
// EventMessage Tests
// -------------------------------------------------------------

TEST(EventMessage, ConstructFromJsonValid)
{
    Json json = {
        {"regex", "event_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 1}, {"name", "task_from"}, {"description", "from"}},
          {{"index", 2}, {"name", "task_to"}, {"description", "to"}},
          {{"index", 3}, {"name", "message_text"}, {"description", "text"}}}}};

    EventMessage e(json);

    EXPECT_EQ(e.getFromPos(), 1);
    EXPECT_EQ(e.getToPos(), 2);
    EXPECT_EQ(e.getTextPos(), 3);
}

TEST(EventMessage, MissingMessageThrows)
{
    Json json = {
        {"regex", "event_regex"},
        {"groups",
         {{{"index", 0}, {"name", "timestamp"}, {"description", "timestamp"}},
          {{"index", 1}, {"name", "task_from"}, {"description", "from"}},
          {{"index", 2}, {"name", "task_to"}, {"description", "to"}}}}};

    EXPECT_THROW(EventMessage e(json), TxtImportException);
}

// -------------------------------------------------------------
// Equality Tests
// -------------------------------------------------------------

TEST(Note, EqualityWorks)
{
    Note a("x", 0, 1);
    Note b("x", 0, 1);

    EXPECT_TRUE(a == b);
}

TEST(Note, InequalityWorks)
{
    Note a("x", 0, 1);
    Note b("x", 0, 2);

    EXPECT_FALSE(a == b);
}

TEST(StateMachine, Equality)
{
    StateMachine a("x", 0, 1, 2);
    StateMachine b("x", 0, 1, 2);

    EXPECT_TRUE(a == b);
}

TEST(TaskSwitch, Inequality)
{
    TaskSwitch a("x", 0, 1, 2);
    TaskSwitch b("x", 0, 1, 3);

    EXPECT_FALSE(a == b);
}

TEST(EventMessage, Equality)
{
    EventMessage a("x", 0, 1, 2, 3);
    EventMessage b("x", 0, 1, 2, 3);

    EXPECT_TRUE(a == b);
}

TEST(EventMessage, Inequality)
{
    EventMessage a("x", 0, 1, 2, 3);
    EventMessage b("x", 0, 1, 2, 4);

    EXPECT_FALSE(a == b);
}

}  // namespace test