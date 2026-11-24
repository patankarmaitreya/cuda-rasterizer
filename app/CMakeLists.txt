add_executable(
    render_demo
    render_demo.cpp
)

target_link_libraries(
    render_demo
    PRIVATE CUDA-RASTERIZER::ops
    PRIVATE CUDA-RASTERIZER::math
    PRIVATE CUDA-RASTERIZER::raster
)

target_compile_options(
    render_demo
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

install(
    TARGETS render_demo
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
