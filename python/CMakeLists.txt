#  Copyright (c) 2023 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

cmake_minimum_required(VERSION 3.27)

project(warp-py LANGUAGES CXX)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

set(COMMON_FILES
        ops.cpp
)

# Add a library using FindPython's tooling (pybind11 also provides a helper like this)
python_add_library(py_core MODULE ${COMMON_FILES} WITH_SOABI)
target_link_libraries(py_core PRIVATE pybind11::headers)

# The install directory is the output (wheel) directory
install(TARGETS py_core DESTINATION warp-py)
