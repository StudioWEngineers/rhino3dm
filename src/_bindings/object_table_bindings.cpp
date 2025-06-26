#include "../object_table.h"
#include "casters/uuid_caster.h"
#include "point_geometry_bindings.h"


nb::object GeometryObjectWrapper(const std::shared_ptr<ON_Object>& geom) {
    if (geom == nullptr) {
        throw nb::stop_iteration();
    }

    if (ON_Point* pt = dynamic_cast<ON_Point*>(geom.get())) {
        return nb::cast(pt, nb::rv_policy::reference);
    }

    if (ON_Curve* crv = dynamic_cast<ON_Curve*>(geom.get())) {

        if (ON_LineCurve* lc = dynamic_cast<ON_LineCurve*>(geom.get())) {
            return nb::cast(lc, nb::rv_policy::reference);
        }

        return nb::cast(crv, nb::rv_policy::reference);
    }

    return nb::cast(geom.get(), nb::rv_policy::reference);
}

void ObjectTableBindings(nb::module_& m) {

    nb::class_<ObjectTable::Iterator>(m, "__ObjectTableIterator")

        .def("__iter__", [](ObjectTable::Iterator& it) -> ObjectTable::Iterator& { return it; })

        .def("__next__", [](ObjectTable::Iterator& it) -> nb::object {
                if (it.IsOver()) {
                    throw nb::stop_iteration();
                }

                auto geom = *it;
                ++it;

                return GeometryObjectWrapper(geom);
            }
        )
    ;

    nb::class_<ObjectTable>(m, "ObjectTable")
        /*magic methods*/
        .def("__iter__", [](ObjectTable& self) {return self.Begin();}, nb::keep_alive<0, 1>())

        /*other methods*/
        .def("max_index", &ObjectTable::MaxIndex)
        .def("add", &ObjectTable::Add)
        .def("delete_by_uuid", &ObjectTable::DeleteByUUID)
    ;
}
