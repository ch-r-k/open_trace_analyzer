###########################################################################

cmake_minimum_required (VERSION 3.17)

set(TOOLCHAIN X86_GCC)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/arm_setup/cmake")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/src/platform")


if("${TOOLCHAIN}" STREQUAL "X86_GCC")
    set(CMAKE_TOOLCHAIN_FILE ./arm_setup/cmake/x86-gcc-toolchain.cmake)  # ← use specific file!
else()
    message(FATAL_ERROR "unsupported toolchain: ${TOOLCHAIN}")
endif()


set(PROJECT open_trace_analyzer)

include(device)
include(utils)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT} LANGUAGES C CXX ASM)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "")
endif ()

set(INCLUDE_DIRS
    src
)

## Application source files
# C++ source files
## Application source files (device-independent)
set(APP_CPP_SRCS
    src/main.cpp
)


include_directories(${INCLUDE_DIRS})

add_executable( ${PROJECT} 
                ${APP_CPP_SRCS})

target_include_directories(${PROJECT} PRIVATE include)

# Add 3rdparty folder
add_subdirectory(src/3d_party)
add_subdirectory(src EXCLUDE_FROM_ALL)


# Later, link it to your target
target_link_libraries(${PROJECT} PRIVATE nlohmann_json::nlohmann_json)

set(WARNINGS
    all
    extra
    maybe-uninitialized
    strict-overflow=2
    switch
    write-strings
)

list(TRANSFORM WARNINGS PREPEND "-W")
list(TRANSFORM DISABLE_WARNINGS PREPEND "-Wno-")
target_compile_options(${PROJECT} PRIVATE "${WARNINGS}" "${DISABLE_WARNINGS}")
if (FATAL_ERRORS)
    target_compile_options(${PROJECT} PRIVATE "-Wfatal-errors")
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-volatile")


set(LAUNCH_FILE_INTERMEDIATE "${CMAKE_CURRENT_BINARY_DIR}/launch.json.in")
configure_file("${CMAKE_CURRENT_LIST_DIR}/arm_setup/cmake/launch.json.in" ${LAUNCH_FILE_INTERMEDIATE} @ONLY)

file(GENERATE
    OUTPUT "${CMAKE_CURRENT_LIST_DIR}/.vscode/launch.json"
    INPUT ${LAUNCH_FILE_INTERMEDIATE}
)