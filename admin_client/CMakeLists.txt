cmake_minimum_required(VERSION 3.7)
project(admin_client C)

# Turn verbose on
# set( CMAKE_VERBOSE_MAKEFILE on )

# Standard and compiler flags
set(CMAKE_C_STANDARD 99)
add_compile_options(-pedantic -Wall)
include_directories(src/include)

add_subdirectory(src)
