#pragma once

#include "application/app.hpp"
#include "application/import/task_objects/import_object.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"
#include "application/user_control/command_line_arg.hpp"

namespace application
{
class ApplicationManager
{
   public:
    ApplicationManager(int argc, char* argv[]);
    ~ApplicationManager() = default;
    int execute(void);

   private:
    user_control::CommandLineArgs cmd;
    import::ImportObject object_import;
    import::ImportTrace qspy_import;
    export_data::seq_diagram::Puml puml_export;
    App application;
};
}  // namespace application