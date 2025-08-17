#pragma once

#include "application/app.hpp"
#include "application/import/task_objects/import_object.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"

namespace application
{
class ApplicationManager
{
   public:
    ApplicationManager();
    ~ApplicationManager() = default;
    int execute(void);

   private:
    import::ImportObject object_import;
    import::ImportTrace qspy_import;
    export_data::seq_diagram::Puml puml_export;
    App application;
};
}  // namespace application