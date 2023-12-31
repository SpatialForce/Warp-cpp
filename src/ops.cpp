//  Copyright (c) 2023 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include <pybind11/pybind11.h>
#include "runtime/warp.h"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(warp_core, m) {
    m.doc() = R"pbdoc(
        Warp runtime
        -----------------------

        .. currentmodule:: warp_runtime_py

        .. autosummary::
           :toctree: _generate

           add
           subtract
           cuda_driver_version
           cuda_toolkit_version
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("cuda_driver_version", &cuda_driver_version, R"pbdoc(
        Get Cuda version
    )pbdoc");

    m.def("cuda_toolkit_version", &cuda_toolkit_version, R"pbdoc(
        Get Cuda toolkit version
    )pbdoc");

    m.def("cuda_device_get_name", &cuda_device_get_name, R"pbdoc(
        Get Cuda device name
    )pbdoc");

    m.def("init", &init, R"pbdoc(
        init Cuda
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

    m.attr("__version__") = "dev";
}
