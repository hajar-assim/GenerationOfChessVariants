cmake_minimum_required(VERSION 3.14)
project(chess_variant VERSION 1.0.0 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Find Cadmium v2 (expected via CADMIUM environment variable)
if(DEFINED ENV{CADMIUM})
    set(CADMIUM_INCLUDE_DIR $ENV{CADMIUM})
    message(STATUS "Cadmium found at: ${CADMIUM_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "CADMIUM environment variable not set. Please set it to the Cadmium v2 include directory.")
endif()

# Find nlohmann_json (typically bundled with Cadmium or system-installed)
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found via find_package, using header-only from Cadmium")
endif()

# Add subdirectory for main simulation
add_subdirectory(main)
