cmake_minimum_required(VERSION 3.0)

aux_source_directory(src SOURCE)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

INCLUDE_DIRECTORIES(./include)

project(Cpp-Server)

add_executable(${PROJECT_NAME} ${SOURCE})