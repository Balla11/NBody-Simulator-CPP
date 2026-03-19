cmake_minimum_required(VERSION 3.20)
project(NBodySimulator VERSION 1.0 LANGUAGES CXX)

# Using C++20 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


file(GLOB_RECURSE SOURCES "src/*.cpp")


add_executable(${PROJECT_NAME} ${SOURCES})


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()