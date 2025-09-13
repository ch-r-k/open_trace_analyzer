set(SOURCE
    manager/manager.cpp

    application/app.cpp
    application/user_control/command_line_arg.cpp
    application/user_control/user_input_handler.cpp
    application/configuration/config_handler.cpp

    application/task_object/task_object.cpp
    application/trace_entry/event_message/event_message.cpp
    application/trace_entry/state_machine/state_machine.cpp
    application/trace_entry/task_switch/task_switch.cpp
    application/trace_entry/trace_entry.cpp

    import/task_objects/import_object.cpp
    import/trace_files/txt_import/import_trace.cpp

    export/sequence_diagram/puml/export_puml.cpp
    export/sequence_diagram/puml/export_puml_timing.cpp
)

target_sources(${PROJECT}_lib PRIVATE ${SOURCE})