include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(
    rasterizer_tests
    test_cuda_ops.cpp
    test_vec3.cpp
    test_mat4.cpp
    test_vec4.cpp
    test_transform.cpp
    test_framebuffer.cpp
    test_depthbuffer.cpp
    test_rasterizer.cpp
)

target_link_libraries(
    rasterizer_tests
    PRIVATE
        GTest::gtest_main
        CUDA-RASTERIZER::ops
        CUDA-RASTERIZER::math
        CUDA-RASTERIZER::raster
)

include(GoogleTest)

gtest_discover_tests(rasterizer_tests)