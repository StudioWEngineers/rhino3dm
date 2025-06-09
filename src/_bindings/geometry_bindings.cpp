#include "geometry_bindings.h"


void GeometryBindings(nb::module_& m) {
    nb::class_<ON_Geometry>(m, "Geometry")
        .def(nb::init<>())
        //.def("__repr__", &Layer::ToString)

        .def("clear_bounding_box", &ON_Geometry::ClearBoundingBox)
        .def("dimension", &ON_Geometry::Dimension)
        .def("is_deformable", &ON_Geometry::IsDeformable)
        //.def("is_valid", &ON_Geometry::IsValid)
        .def("scale", &ON_Geometry::Scale)
        .def("swap_coordinates", &ON_Geometry::SwapCoordinates)
    ;
}
