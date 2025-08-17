#include "manager.hpp"
#include <iostream>
#include "application/app.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"
#include "application/import/trace_files/import_trace.hpp"

namespace application
{
ApplicationManager::ApplicationManager(int argc, char* argv[])
    : cmd{argc, argv},
      object_import{"test/input_files/qspy_ao.json"},
      qspy_import{"test/input_files/qpsy.txt"},
      puml_export{"test/export_file.puml"},
      application{object_import, qspy_import, puml_export}

{
}

int ApplicationManager::execute(void)
{
    if (cmd.hasFlag("--help"))
    {
        std::cout << "Help requested!\n";
    }

    try
    {
        application.importData();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught in Import: " << e.what() << std::endl;
        return 1;
    }

    try
    {
        application.combineTraces();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught in Trace Combining: " << e.what()
                  << std::endl;
        return 1;
    }

    try
    {
        application.exportData();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught in Exporting: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
}  // namespace application