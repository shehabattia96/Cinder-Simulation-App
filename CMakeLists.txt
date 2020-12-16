cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
project( CinderSimulationApp VERSION 1.0.0 DESCRIPTION "Tools and examples to quickly get objects drawn on the screen using Cinder.")

set(CINDER_EXTRN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/externals/Cinder" CACHE STRING "Path to Cinder")

option(BUILD_EXAMPLES "Build examples" OFF)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()