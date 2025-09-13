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

}  // namespace application
namespace manager
{

using application::App;
using application::config::ConfigHandler;
using application::export_data::seq_diagram::ISeqDiagram;
using application::import::ImportObject;
using application::import::ImportTrace;
using application::user_control::UserInputHandler;

class ApplicationManager
{
   public:
    ApplicationManager(int argc, const char* argv[]);
    ~ApplicationManager();
    int execute(void);

   private:
    void build(void);
    UserInputHandler user_input;
    std::unique_ptr<ConfigHandler> config_handler;

    std::unique_ptr<ImportObject> object_import;
    std::unique_ptr<ImportTrace> qspy_import;
    std::unique_ptr<ISeqDiagram> seq_export;

    std::unique_ptr<App> application;
};
}  // namespace manager