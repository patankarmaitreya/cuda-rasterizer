include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(
    rasterizer_tests
    test_cuda_ops.cpp
)

target_link_libraries(
    rasterizer_tests
    PRIVATE
        GTest::gtest_main
        CUDA-RASTERIZER::ops
)

include(GoogleTest)

gtest_discover_tests(rasterizer_tests)