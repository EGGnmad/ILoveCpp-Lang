cmake_minimum_required(VERSION 3.26)

project(ILOVEC++ LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for intellisense

include_directories(include)
add_subdirectory(src)