#pragma once

#include "application/user_control/command_line_arg.hpp"
#include "application/user_control/user_input_handler.hpp"

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
}

using export_data::seq_diagram::Puml;
using import::ImportObject;
using import::ImportTrace;

class ApplicationManager
{
   public:
    ApplicationManager(int argc, char* argv[]);
    ~ApplicationManager();
    int execute(void);

   private:
    user_control::UserInputHandler user_input;
    ImportObject* object_import;
    ImportTrace* qspy_import;
    Puml* puml_export;
    App* application;
};
}  // namespace application