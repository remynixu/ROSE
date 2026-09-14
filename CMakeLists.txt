cmake_minimum_required(VERSION 3.15)
project("ROSE" C)

set(C_STANDARD 90)
set(C_STANDARD_REQUIRED ON)

set(ROSE_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME})

add_subdirectory(src)