#  Copyright (c) 2023 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

cmake_minimum_required(VERSION 3.27)

project(
        ${SKBUILD_PROJECT_NAME}
        VERSION ${SKBUILD_PROJECT_VERSION}
        LANGUAGES CXX)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

set(COMMON_FILES
        ops.cpp
)

# Add a library using FindPython's tooling (pybind11 also provides a helper like this)
python_add_library(warp_core MODULE ${COMMON_FILES} WITH_SOABI)
target_link_libraries(warp_core PRIVATE pybind11::headers)

target_compile_definitions(warp_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

# The install directory is the output (wheel) directory
install(TARGETS warp_core DESTINATION warp_runtime_py)
