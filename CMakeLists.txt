###########################################################################
# CMake minimum version
cmake_minimum_required(VERSION 3.17)

# Project
set(PROJECT open_trace_analyzer)
project(${PROJECT} LANGUAGES C CXX ASM)

###########################################################################
# Toolchain
set(TOOLCHAIN X86_GCC)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/arm_setup/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/src/platform")

if("${TOOLCHAIN}" STREQUAL "X86_GCC")
    set(CMAKE_TOOLCHAIN_FILE ./arm_setup/cmake/x86-gcc-toolchain.cmake)
else()
    message(FATAL_ERROR "unsupported toolchain: ${TOOLCHAIN}")
endif()

###########################################################################
# C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "")
endif ()

###########################################################################
# GoogleTest setup
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Keep the project compiler flags
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

###########################################################################
# Include directories
set(INCLUDE_DIRS src)
include_directories(${INCLUDE_DIRS})


###########################################################################
# Build application library
set(APP_CPP_SRCS
    src/main.cpp
)

add_library(${PROJECT}_lib STATIC ${APP_CPP_SRCS})
target_include_directories(${PROJECT}_lib PUBLIC ${INCLUDE_DIRS})
target_compile_options(${PROJECT}_lib PRIVATE "${WARNINGS}" "${DISABLE_WARNINGS}")
target_link_libraries(${PROJECT}_lib PUBLIC nlohmann_json::nlohmann_json)



###########################################################################
# Application sources
add_executable(${PROJECT} src/main.cpp)
target_link_libraries(${PROJECT} PRIVATE ${PROJECT}_lib)

###########################################################################
# Link third-party folder (if needed)
add_subdirectory(src/3d_party)
add_subdirectory(src EXCLUDE_FROM_ALL)

###########################################################################
# # Test executable
set(TEST_SRCS
    src/test/sys_test.cpp
    src/application/task_object/test.cpp
    # add more test files here
)

add_executable(${PROJECT}_tests ${TEST_SRCS})

target_include_directories(${PROJECT}_tests PRIVATE src include)
target_link_libraries(${PROJECT}_tests PRIVATE gtest gtest_main  ${PROJECT}_lib nlohmann_json::nlohmann_json)

# Optionally reuse warnings
target_compile_options(${PROJECT}_tests PRIVATE "${WARNINGS}" "${DISABLE_WARNINGS}")

# Enable testing
enable_testing()
add_test(NAME Tests COMMAND ${PROJECT}_tests)


###########################################################################
# Warnings
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

if(FATAL_ERRORS)
    target_compile_options(${PROJECT} PRIVATE "-Wfatal-errors")
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-volatile")

###########################################################################
# Launch file generation (for VSCode)
set(LAUNCH_FILE_INTERMEDIATE "${CMAKE_CURRENT_BINARY_DIR}/launch.json.in")
configure_file("${CMAKE_CURRENT_LIST_DIR}/arm_setup/cmake/launch.json.in" ${LAUNCH_FILE_INTERMEDIATE} @ONLY)
file(GENERATE
    OUTPUT "${CMAKE_CURRENT_LIST_DIR}/.vscode/launch.json"
    INPUT ${LAUNCH_FILE_INTERMEDIATE}
)