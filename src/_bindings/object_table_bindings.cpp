#include "../object_table.h"
#include "uuid_caster.h"
#include <iostream>


void ObjectTableBindings(nb::module_& m) {
    nb::class_<ON_Geometry>(m, "ON_Geometry")
        .def("__repr__", [](const ON_Geometry& self) {
            return "<ON_Geometry>";
        })
    ;
    nb::class_<ON_Point, ON_Geometry>(m, "PointView")
        .def("x", [](const ON_Point& pt) { return pt.point.x; })
        .def("y", [](const ON_Point& pt) { return pt.point.y; })
        .def("z", [](const ON_Point& pt) { return pt.point.z; })
    ;

    nb::class_<ObjectTable::Iterator>(m, "__ObjectTableIterator")
        .def("__iter__", [](ObjectTable::Iterator& it) -> ObjectTable::Iterator& { return it; })
        .def("__next__", [](ObjectTable::Iterator& it) -> nb::object {
            if (it.IsOver())
                throw nb::stop_iteration();

            auto geom = *it;
            ++it;

            if (!geom)
                throw nb::stop_iteration();

            // Try raw pointer cast first with dynamic_cast manually
            if (ON_Point* pt = dynamic_cast<ON_Point*>(geom.get())) {
                std::cout << "successfull cast" << std::endl;
                return nb::cast(pt, nb::rv_policy::reference);
            }

            // Add more dynamic_casts for other known subclasses here...

            // Fallback, return base as borrowed reference
            std::cout << "NOT successfull cast" << std::endl;
            return nb::cast(geom.get(), nb::rv_policy::reference);
        })
    ;

    nb::class_<ObjectTable>(m, "ObjectTable")
        .def("__iter__", [](ObjectTable& self) {return self.Begin();}, nb::keep_alive<0, 1>())
        .def("max_index", &ObjectTable::MaxIndex)
        .def("add", &ObjectTable::Add)
        .def("delete_by_uuid", &ObjectTable::DeleteByUUID, nb::arg("object_uuid"))
    ;
}
