#pragma once

#include "bindings.h"
#include "../lib/opennurbs/opennurbs_color.h"

namespace nanobind::detail {

template <>
struct type_caster<ON_Color> {
public:
    NB_TYPE_CASTER(ON_Color, const_name("tuple"));

    // Python → C++
    bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept {
        //if (!isinstance<tuple>(src) || len(src) != 4)
        if (!py::isinstance<py::tuple>(src) || py::len(src) != 4)
        //if (!py::isinstance<py::tuple<>>(src) || py::len(src) != 4)
            return false;

        try {
            int r = cast<int>(src[0]);
            int g = cast<int>(src[1]);
            int b = cast<int>(src[2]);
            int a = cast<int>(src[3]);

            // Invert alpha channel (Python uses standard alpha, OpenNURBS inverts)
            value = ON_Color(r, g, b, 255 - a);
            return true;
        } catch (...) {
            return false;
        }
    }

    // C++ → Python
    static handle from_cpp(const ON_Color& color, rv_policy, cleanup_list*) noexcept {
        int r = color.Red();
        int g = color.Green();
        int b = color.Blue();
        int a = 255 - color.Alpha();  // Invert alpha to match Python expectation
        return py::make_tuple(r, g, b, a).release();
    }
};

} // namespace nanobind::detail
