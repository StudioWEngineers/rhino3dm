#include "geometry_bindings.h"
#include "point_geometry_bindings.h"


void PointGeometryBindings(nb::module_& m) {

    nb::class_<ON_Point, ON_Geometry>(m, "PointGeometry")

        /*magic methods*/
        .def(nb::init<>())
        .def(nb::init<double, double, double>())
        .def(nb::init<ON_3dPoint>())

        /*read-write methods*/
        .def_rw("point", &ON_Point::point)

        /*other methods*/
        .def("is_valid", &ON_Point::IsValid, nb::arg("text_log") = nullptr)
    ;
}
