#include "point3d_bindings.h"


void Point3dBindings(nb::module_& m) {

    nb::class_<ON_3dPoint>(m, "Point3d")

        /*magic methods*/
        .def(nb::init<double, double, double>())
        .def("__add__", [] (const ON_3dPoint& self, const ON_3dPoint& other) {
            return self + other;
            }
        )
        .def("__eq__", [] (const ON_3dPoint& self, const ON_3dPoint& other) {
            return self == other;
            }
        )
        .def("__mul__", [] (ON_3dPoint& self, double value) {
            return self * value;
            }
        )
        .def("__ne__", [] (const ON_3dPoint& self, const ON_3dPoint& other) {
            return self != other;
            }
        )
        .def("__truediv__", [] (ON_3dPoint& self, double value) {
            return self / value;
            }
        )

        /*read-write methods*/
        .def_rw("x", &ON_3dPoint::x)
        .def_rw("y", &ON_3dPoint::y)
        .def_rw("z", &ON_3dPoint::z)

        /*other methods*/
        .def("distance_to", &ON_3dPoint::DistanceTo)
        .def("is_coincident", &ON_3dPoint::IsCoincident)
    ;
}
