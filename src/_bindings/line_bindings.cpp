#include "line_bindings.h"


void LineBindings(nb::module_& m) {

    nb::class_<ON_Line>(m, "Line")

        /*magic methods*/
        .def(nb::init<>())

        .def(nb::init<ON_3dPoint, ON_3dPoint>())

        .def("__eq__", [] (const ON_Line& self, const ON_Line& other) {
            return self == other;
            }
        )

        .def("__getitem__",
            [](const ON_Line& line, int index) -> const ON_3dPoint& {
                if (index < 0 || index > 1) {
                    throw nb::index_error("index must be 0 or 1");
                }
                return line[index];
            },
            nb::rv_policy::reference_internal
        )

        .def("__ne__", [] (const ON_Line& self, const ON_Line& other) {
            return self != other;
            }
        )

        .def("__setitem__",
            [](ON_Line& line, int index, const ON_3dPoint& pt) {
                if (index < 0 || index > 1) {
                    throw nb::index_error("index must be 0 or 1");
                }
                line[index] = pt;
            }
        )

        /*other methods*/
        .def("create",
            [](ON_Line& self, const ON_3dPoint& from, const ON_3dPoint& to) {
            return self.Create(from, to);
            }
        )

        .def("distance_to", &ON_Line::DistanceTo)

        .def("is_valid", &ON_Line::IsValid)

        .def("length", &ON_Line::Length)

        .def("point_at", &ON_Line::PointAt)
    ;
}
