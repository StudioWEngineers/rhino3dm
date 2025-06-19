#include "line_bindings.h"


void LineBindings(nb::module_& m) {
    nb::class_<ON_Line>(m, "Line")
        .def(nb::init<ON_3dPoint, ON_3dPoint>())
        .def("__getitem__",
            [](const ON_Line& line, int index) -> const ON_3dPoint& {
                if (index < 0 || index > 1) {
                    throw nb::index_error("index must be 0 or 1");
                }
                return line[index];
            },
            nb::rv_policy::reference_internal
        )
        .def("__setitem__",
            [](ON_Line& line, int index, const ON_3dPoint& pt) {
                if (index < 0 || index > 1) {
                    throw nb::index_error("index must be 0 or 1"); //std::out_of_range("Index must be 0 or 1");
                }
                line[index] = pt;
            }
        )

        .def("create", [](ON_Line& self, const ON_3dPoint& from, const ON_3dPoint& to) {
            return self.Create(from, to);
        })
        //.def_rw("from", [](const ON_Line& self) { return self.from; },
        //                        [](ON_Line& self, const ON_3dPoint& pt) { self.from = pt; })
        //.def_rw("to", [](const ON_Line& self) { return self.to; },
        //                      [](ON_Line& self, const ON_3dPoint& pt) { self.to = pt; })
        .def("is_valid", &ON_Line::IsValid)
        .def("length", &ON_Line::Length)
        .def("direction", &ON_Line::Direction)
        //.def("closest_point_to", &ON_Line::ClosestPointTo, nb::arg("point"))
        //.def("evaluate", [](const ON_Line& line, double t) {
        //    ON_3dPoint result;
        //    line.Evaluate(t, result);
        //    return result;
        //}, nb::arg("t"))
        //.def("__repr__", [](const ON_Line& line) {
        //    return "<Line from=({}, {}, {}) to=({}, {}, {})>"_format(
        //        line.from.x, line.from.y, line.from.z,
        //        line.to.x, line.to.y, line.to.z);
        //})
    ;

//    nb::class_<ON_LineCurve>(m, "Line")
//        .def(nb::init<>())
//        .def(nb::init<ON_3dPoint, ON_3dPoint>())
//
//        .def("is_valid", &ON_LineCurve::IsValid)
//        .def("dimension", &ON_LineCurve::Dimension)
//        .def_prop_ro("length", [](const ON_LineCurve& self) {
//            return self.m_line.Length();
//        })
//
//        .def_prop_rw("line",
//            [](const ON_LineCurve& self) { return self.m_line; },
//            [](ON_LineCurve& self, const ON_Line& l) { self.m_line = l; })
//    ;
}
