#  Copyright (c) 2023 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

cmake_minimum_required(VERSION 3.27)

project(runtime LANGUAGES C CXX CUDA)

set(COMMON_FILES
        cuda_util.h
        cuda_util.cpp
        warp.h
        warp.cpp
        warp.cu
        scan.h
        scan.cpp
        scan.cu
)

set(TYPE_FILES
        array.h
        radix_sort.h
        radix_sort.cu
        scan.h
        scan.cu
        hash_grid.h
        hash_grid.cu
        bvh.h
        bvh.cu
        mesh.h
        mesh.cu
)

source_group("common\\" FILES ${COMMON_FILES})

set(PROJECT_FILES
        ${COMMON_FILES}
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(${PROJECT_NAME} PRIVATE
        CUDA::cudart_static
        CUDA::nvrtc_static
        CUDA::nvrtc_builtins_static
        CUDA::nvptxcompiler_static
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
        WP_ENABLE_CUDA_COMPATIBILITY=1
        WP_ENABLE_CUDA=1
        WP_ENABLE_CUTLASS=0
        WP_ENABLE_DEBUG=0
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} .
        ../warp-header)