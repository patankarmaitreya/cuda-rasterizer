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

add_library(
    raster
    raster/framebuffer.cpp
    raster/depthbuffer.cpp
    raster/rasterizer.cpp
    raster/renderer.cpp
)

add_library(
    CUDA-RASTERIZER::raster
    ALIAS raster
)

target_compile_features(
    ops
    PUBLIC cxx_std_17
)

target_compile_features(
    math
    PUBLIC cxx_std_17
)

target_compile_features(
    raster
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

target_include_directories(
    raster
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"   
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(raster PUBLIC math)

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

install(
    TARGETS raster
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)