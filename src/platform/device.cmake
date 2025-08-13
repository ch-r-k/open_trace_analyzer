# Architecture-independent feature flags
set(FEATURE_FLAGS
    -ffunction-sections
    -fdata-sections
)

# Optional: defines for x86-specific code
set(DEVICE_DEFINES
    PLATFORM_X86
)

# Apply compile definitions globally
add_compile_definitions(${DEVICE_DEFINES})

# Compilation and linking flags
set(COMPILE_FLAGS_LIST "${FEATURE_FLAGS}")
set(LINKER_FLAGS_LIST
    -Wl,--gc-sections
    -pthread
)

# Join lists into space-separated strings
list(JOIN COMPILE_FLAGS_LIST " " COMPILE_FLAGS)
list(JOIN LINKER_FLAGS_LIST " " EXE_LINKER_FLAGS)

# Append flags to CMake variables
string(APPEND CMAKE_C_FLAGS " ${COMPILE_FLAGS}")
string(APPEND CMAKE_CXX_FLAGS " ${COMPILE_FLAGS}")
string(APPEND CMAKE_EXE_LINKER_FLAGS " ${EXE_LINKER_FLAGS}")
