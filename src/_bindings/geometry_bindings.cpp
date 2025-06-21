#include "geometry_bindings.h"


void GeometryBindings(nb::module_& m) {

    nb::class_<ON_Geometry, ON_Object>(m, "Geometry")

        /*magic methods*/
        .def(nb::init<>())

        /*other methods*/
        .def("dimension", &ON_Geometry::Dimension)

        .def("is_deformable", &ON_Geometry::IsDeformable)

        .def("is_valid", &ON_Geometry::IsValid, nb::arg("text_log") = nullptr)
    ;
}
