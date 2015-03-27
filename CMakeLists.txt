cmake_minimum_required(VERSION 2.8)
project(z80)

# Include /cmake directory when looking for modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Find required packages: SDL, Check...
find_package(Check REQUIRED)

add_subdirectory(libzeta80)
add_subdirectory(tests)
