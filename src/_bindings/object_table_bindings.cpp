#include "../object_table.h"
#include "casters/uuid_caster.h"
#include "point_geometry_bindings.h"

//switch (geom->ObjectType()) {
//    case ON::point_object:
//        return nb::cast(static_cast<ON_Point*>(geom), nb::rv_policy::reference);
//    case ON::curve_object:
//        return nb::cast(static_cast<ON_Curve*>(geom), nb::rv_policy::reference);
//    // ...
//    default:
//        return nb::cast(geom, nb::rv_policy::reference);
//}
void ObjectTableBindings(nb::module_& m) {

    nb::class_<ObjectTable::Iterator>(m, "__ObjectTableIterator")

        .def("__iter__", [](ObjectTable::Iterator& it) -> ObjectTable::Iterator& { return it; })

        .def("__next__", [](ObjectTable::Iterator& it) -> nb::object {
                if (it.IsOver()) {
                    throw nb::stop_iteration();
                }

                auto geom = *it;
                ++it;

                if (!geom) // do I need this?
                    throw nb::stop_iteration();

                // Try raw pointer cast first with dynamic_cast manually
                if (ON_Point* pt = dynamic_cast<ON_Point*>(geom.get())) {
                    return nb::cast(pt, nb::rv_policy::reference);
                }

                // Add more dynamic_casts for other known subclasses here...

                // Fallback, return base as borrowed reference
                return nb::cast(geom.get(), nb::rv_policy::reference);
            }
        )
    ;

    nb::class_<ObjectTable>(m, "ObjectTable")
        .def("__iter__", [](ObjectTable& self) {return self.Begin();}, nb::keep_alive<0, 1>())
        .def("max_index", &ObjectTable::MaxIndex)
        .def("add", &ObjectTable::Add)
        .def("delete_by_uuid", &ObjectTable::DeleteByUUID, nb::arg("object_uuid"))
    ;
}
