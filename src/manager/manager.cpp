#include "manager.hpp"
#include <iostream>
#include <stdexcept>
#include "application/app.hpp"
#include "export/sequence_diagram/puml/export_puml.hpp"
#include "configuration/config_handler.hpp"
#include "configuration/config_types.hpp"
#include "import/task_objects/import_object.hpp"
#include "import/trace_files/txt_import/import_trace.hpp"
#include "export/sequence_diagram/puml/export_puml.hpp"
#include "export/sequence_diagram/puml/export_puml_timing.hpp"
#include "export/sequence_diagram/open_trace_viewer/open_trace_viewer.hpp"

namespace manager
{
using export_data::seq_diagram::OpenTraceViewer;
using export_data::seq_diagram::Puml;
using export_data::seq_diagram::PumlTiming;
using manager::config::InputType;
using manager::config::OutputType;

ApplicationManager::ApplicationManager(int argc, const char* argv[])
    : user_input{argc, argv}

{
}

ApplicationManager::~ApplicationManager() {}

int ApplicationManager::execute(void)
{
    config_handler =
        std::make_unique<ConfigHandler>(user_input.getConfigFileName());

    try
    {
        selectFiles();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught at file selection: " << e.what()
                  << std::endl;
        return 1;
    }

    try
    {
        build();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught at Application building: " << e.what()
                  << std::endl;
        return 1;
    }

    application =
        std::make_unique<App>(*object_import, *qspy_import, *seq_export);

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
void ApplicationManager::selectFiles(void)
{
    task_object_file_name = config_handler->getTaskObjectFileName();
    trace_file_name = config_handler->getTraceFileName();
    output_file_name = config_handler->getOutputFileName();

    if (user_input.getTaskObjectFileName() != "")
    {
        task_object_file_name = user_input.getTaskObjectFileName();
    }

    if (user_input.getTraceFileName() != "")
    {
        trace_file_name = user_input.getTraceFileName();
    }

    if (user_input.getOutputFileName() != "")
    {
        output_file_name = user_input.getOutputFileName();
    }
}

void ApplicationManager::build(void)
{
    switch (config_handler->getInputFormat())
    {
        case InputType::TXT:
        {
            object_import =
                std::make_unique<ImportObject>(task_object_file_name);

            qspy_import = std::make_unique<ImportTrace>(
                trace_file_name,  //
                *config_handler->getEventMessageConfig(),
                *config_handler->getStateMachineConfig(),
                *config_handler->getTaskSwitchConfig(),
                *config_handler->getNoteConfig());

            break;
        }
        case InputType::BIN:
        {
            throw std::runtime_error("not implemented");
        }
    }

    switch (config_handler->getOutputFormat())
    {
        case OutputType::PUML_SEQ:
        {
            seq_export = std::make_unique<Puml>(output_file_name);
            break;
        }
        case OutputType::PUML_TIMING:
        {
            seq_export = std::make_unique<PumlTiming>(output_file_name);
            break;
        }
        case OutputType::OPEN_TRACE_VIEWER:
        {
            seq_export = std::make_unique<OpenTraceViewer>(output_file_name);
            break;
        }
    }
}
}  // namespace manager