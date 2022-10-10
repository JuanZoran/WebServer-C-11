cmake_minimum_required (VERSION 2.9)

include_directories(include)

project (cpp-Server)

aux_source_directory(src SOURCE)

add_executable(${PROJECT_NAME} ${SOURCE})
