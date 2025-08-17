set(SOURCE
    application/manager.cpp
    application/app.cpp

    application/task_object/task_object.cpp
    application/trace_entry/event_message/event_message.cpp
    application/trace_entry/state_machine/state_machine.cpp
    application/trace_entry/task_switch/task_switch.cpp
    application/trace_entry/trace_entry.cpp

    application/import/task_objects/import_object.cpp
    application/import/trace_files/import_trace.cpp

    application/export/sequence_diagram/puml/export_puml.cpp
)

target_sources(${PROJECT} PRIVATE ${SOURCE})