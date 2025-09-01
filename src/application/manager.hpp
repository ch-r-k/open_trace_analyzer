#pragma once

#include "application/user_control/command_line_arg.hpp"
#include "application/user_control/user_input_handler.hpp"
#include "application/configuration/config_handler.hpp"

namespace application
{
class App;
namespace import
{
class ImportObject;
class ImportTrace;
}  // namespace import

namespace export_data::seq_diagram
{
class Puml;
class PumlTiming;
class ISeqDiagram;
}  // namespace export_data::seq_diagram

using export_data::seq_diagram::ISeqDiagram;
using import::ImportObject;
using import::ImportTrace;

class ApplicationManager
{
   public:
    ApplicationManager(int argc, const char* argv[]);
    ~ApplicationManager();
    int execute(void);

   private:
    void build(void);
    user_control::UserInputHandler user_input;
    config::ConfigHandler* config_handler;
    ImportObject* object_import;
    ImportTrace* qspy_import;
    ISeqDiagram* seq_export;
    App* application;
};
}  // namespace application