#include "manager.hpp"
#include <iostream>
#include "application/app.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/import/task_objects/import_object.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"

namespace application
{
ApplicationManager::ApplicationManager(int argc, const char* argv[])
    : user_input{argc, argv}

{
}

ApplicationManager::~ApplicationManager()
{
    delete application;

    delete object_import;
    delete qspy_import;
    delete puml_export;
}

int ApplicationManager::execute(void)
{
    object_import = new ImportObject{user_input.getTaskObjectFileName()};
    qspy_import = new ImportTrace{user_input.getTraceFileName()};
    puml_export = new Puml{user_input.getOutputFileName()};

    application = new App{*object_import, *qspy_import, *puml_export};

    try
    {
        application->importData();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught in Import: " << e.what() << std::endl;
        return 1;
    }

    try
    {
        application->combineTraces();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught in Trace Combining: " << e.what()
                  << std::endl;
        return 1;
    }

    try
    {
        application->exportData();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught in Exporting: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
}  // namespace application