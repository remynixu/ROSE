cmake_minimum_required(VERSION 3.15)
project("rOSe" C)

set(C_STANDARD 89)
set(C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME})

add_subdirectory(src)