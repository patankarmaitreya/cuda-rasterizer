cmake_minimum_required(VERSION 3.25)

project(
    cuda_rasterizer
    VERSION 1.0.0
    DESCRIPTION "A project to build a rasterizer using cuda"
    LANGUAGES CXX CUDA
)

include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(app)

include(CTest)
add_subdirectory(tests)

add_executable(
    cuda_hello
    hello.cpp
)

target_link_libraries(
    cuda_hello
    PRIVATE CUDA-RASTERIZER::ops
)