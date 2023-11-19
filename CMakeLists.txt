cmake_minimum_required(VERSION 3.5)
project(bench)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "c++ version to use" FORCE)
set(CMAKE_CXX_EXTENSIONS ON CACHE BOOL "use gnu++" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(EXT_DOWNLOAD "allow extcpp downloads" ON)
include(use_ext_foundation.cmake)

ext_use_ext_project_defaults()
ext_declare_dependencies()
ext_colorize_output()

if(NOT TARGET gtest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    find_package(GTest)
    if(NOT TARGET gtest)
        ext_log("downloading googletest")
        FetchContent_MakeAvailable(GoogleTest)
    endif()
endif()

if(NOT TARGET benchmark::benchmark)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    if(NOT TARGET gbench)
        FetchContent_MakeAvailable(GoogleBenchmark)
    endif()
endif()


set(CMAKE_BUILD_TYPE Release)
add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark benchmark::benchmark_main)
target_compile_options(bench PUBLIC "-fno-omit-frame-pointer")
