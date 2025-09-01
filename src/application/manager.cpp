#include "manager.hpp"
#include <iostream>
#include <stdexcept>
#include "application/app.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/configuration/config_handler.hpp"
#include "application/configuration/config_types.hpp"
#include "application/import/task_objects/import_object.hpp"
#include "application/import/trace_files/import_trace.hpp"
#include "application/export/sequence_diagram/puml/export_puml.hpp"
#include "application/export/sequence_diagram/puml/export_puml_timing.hpp"

namespace application
{
using export_data::seq_diagram::Puml;
using export_data::seq_diagram::PumlTiming;

ApplicationManager::ApplicationManager(int argc, const char* argv[])
    : user_input{argc, argv}

{
}

ApplicationManager::~ApplicationManager()
{
    delete config_handler;
    delete application;

    delete object_import;
    delete qspy_import;
    delete seq_export;
}

int ApplicationManager::execute(void)
{
    config_handler = new config::ConfigHandler{user_input.getConfigFileName()};

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

    application = new App{*object_import, *qspy_import, *seq_export};

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

void ApplicationManager::build(void)
{
    switch (config_handler->getInputFormat())
    {
        case config::InputType::TXT:
        {
            object_import =
                new ImportObject{config_handler->getTaskObjectFileName()};
            qspy_import = new ImportTrace{config_handler->getTraceFileName()};
            break;
        }
        case config::InputType::BIN:
        {
            throw std::runtime_error("not implemented");
        }
    }

    switch (config_handler->getOutputFormat())
    {
        case config::OutputType::PUML_SEQ:
        {
            seq_export = new Puml{user_input.getOutputFileName()};
            break;
        }
        case config::OutputType::PUML_TIMING:
        {
            seq_export = new PumlTiming{user_input.getOutputFileName()};
            break;
        }
    }
}
}  // namespace application