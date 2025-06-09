#include "geometry_bindings.h"
#include "point_geometry_bindings.h"


void PointGeometryBindings(nb::module_& m) {
    nb::class_<ON_Point, ON_Geometry>(m, "PointGeometry")
        .def(nb::init<>())
        //.def("__repr__", &Layer::ToString)
        //.def_rw("x", &ON_3dPoint::x)
        //.def_rw("y", &ON_3dPoint::y)
        //.def_rw("z", &ON_3dPoint::z)
        //.def(nb::self + nb::self)
        //.def(nb::self * double())
        ////.def(nb::self + ON_3dVector())
        ////.def(nb::self * ON_Xform())
        //.def(nb::self == nb::self)
        //.def(nb::self != nb::self)
        //.def("distance_to", &ON_3dPoint::DistanceTo)//, py::arg("other"))
        //.def("is_coincident", &ON_3dPoint::IsCoincident)//, py::arg("other"))
    ;
}
