set(SOURCE
    manager/manager.cpp
    manager/user_control/command_line_arg.cpp
    manager/user_control/user_input_handler.cpp
    manager/configuration/config_handler.cpp

    application/app.cpp
    
    types/task_object/task_object.cpp
    types/trace_entry/event_message/event_message.cpp
    types/trace_entry/state_machine/state_machine.cpp
    types/trace_entry/task_switch/task_switch.cpp
    types/trace_entry/trace_entry.cpp

    import/task_objects/import_object.cpp
    import/trace_files/txt_import/import_trace.cpp

    export/sequence_diagram/puml/export_puml.cpp
    export/sequence_diagram/puml/export_puml_timing.cpp
)

target_sources(${PROJECT}_lib PRIVATE ${SOURCE})