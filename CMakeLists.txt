cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
project( BaseCinderApp )


set(CINDER_EXTRN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/externals/Cinder" CACHE STRING "Path to Cinder")


add_subdirectory(examples)
