cmake_minimum_required(VERSION 2.9)

aux_source_directory(src SOURCE)
aux_source_directory(Fd FD)
aux_source_directory(Handler HANDLER)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

INCLUDE_DIRECTORIES(./include Fd Handler)


project(Cpp-Server)

add_executable(${PROJECT_NAME} ${SOURCE} ${FD} ${HANDLER})