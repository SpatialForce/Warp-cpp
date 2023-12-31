#  Copyright (c) 2023 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 20)

enable_language(CUDA)
find_package(CUDAToolkit)
include_directories(${CUDA_INCLUDE_DIRS})

add_subdirectory(runtime)

project(
        ${SKBUILD_PROJECT_NAME}
        VERSION ${SKBUILD_PROJECT_VERSION}
        LANGUAGES CXX)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

set(COMMON_FILES
        src/ops.cpp
)

# Add a library using FindPython's tooling (pybind11 also provides a helper like this)
python_add_library(warp_core MODULE ${COMMON_FILES} WITH_SOABI)

set_property(TARGET warp_core PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(warp_core PRIVATE
        pybind11::headers
        runtime
)

target_include_directories(warp_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ../warp-header
)

target_compile_definitions(warp_core PRIVATE
        WP_ENABLE_CUDA_COMPATIBILITY=1
        WP_ENABLE_CUDA=1
        WP_ENABLE_CUTLASS=0
        WP_ENABLE_DEBUG=0
        VERSION_INFO=${PROJECT_VERSION}
)

# The install directory is the output (wheel) directory
install(TARGETS warp_core DESTINATION warp_runtime_py)