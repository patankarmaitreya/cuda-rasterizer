add_library(
    ops
    cuda_ops.cu
)

add_library(
    CUDA-RASTERIZER::ops
    ALIAS ops
)

add_library(
    math
    math/vec3.cpp
    math/mat4.cpp
    math/vec4.cpp
    math/transform.cpp
)

add_library(
    CUDA-RASTERIZER::math
    ALIAS math
)

target_compile_features(
    ops
    PUBLIC cxx_std_17
)

target_compile_features(
    math
    PUBLIC cxx_std_17
)

target_include_directories(
    ops
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"   
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(
    math
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"   
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(
    TARGETS ops
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
    TARGETS math
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)