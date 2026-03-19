cmake_minimum_required(VERSION 3.20)
project(NBodySimulator VERSION 1.0 LANGUAGES CXX)

# Standard C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_SOURCES
        src/Body.cpp
        src/Simulator.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# WARNINGS
set(MY_WARNINGS -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE ${MY_WARNINGS})
endif()

# --- TEST (GoogleTest) ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 4. TARGET TEST
add_executable(unit_tests tests/test_main.cpp ${LIB_SOURCES})
target_link_libraries(unit_tests GTest::gtest_main)
target_include_directories(unit_tests PUBLIC include)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(unit_tests PRIVATE ${MY_WARNINGS})
endif()