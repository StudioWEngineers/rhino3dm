#include "line_curve_bindings.h"


void LineCurveBindings(nb::module_& m) {

    nb::class_<ON_LineCurve, ON_Geometry>(m, "LineCurve")

        /*magic methods*/
        .def(nb::init<>())
        .def(nb::init<ON_Line>())
        .def(nb::init<ON_3dPoint, ON_3dPoint>())

        /*other methods*/
        .def("dimension", &ON_LineCurve::Dimension)
        .def("is_valid", &ON_LineCurve::IsValid, nb::arg("text_log") = nullptr)
        .def("reverse", &ON_LineCurve::Reverse)
        .def("set_end_point", &ON_LineCurve::SetEndPoint)
        .def("set_start_point", &ON_LineCurve::SetStartPoint)
        .def("swap_coordinates", &ON_LineCurve::SwapCoordinates)

        /*read-write methods*/
        .def_rw("line", &ON_LineCurve::m_line)
    ;
}
