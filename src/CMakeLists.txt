add_library(
    ops
    cuda_ops.cu
)

add_library(
    CUDA-RASTERIZER::ops
    ALIAS ops
)

target_compile_features(
    ops
    PUBLIC cxx_std_17
)

target_include_directories(
    ops
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