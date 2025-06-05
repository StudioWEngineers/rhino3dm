#include "../object_table.h"
#include "uuid_caster.h"


void ObjectTableBindings(nb::module_& m) {
    nb::class_<ON_Geometry>(m, "ON_Geometry")
        .def("__repr__", [](const ON_Geometry& self) {
            return "<ON_Geometry>";
        })
    ;

    nb::class_<ObjectTable::Iterator>(m, "__ObjectTableIterator")
        .def("__iter__", [](ObjectTable::Iterator& it) -> ObjectTable::Iterator& { return it; })
        .def("__next__", [](ObjectTable::Iterator& it) {
            if (it.IsOver())
                throw nb::stop_iteration();

            auto geom = *it;
            ++it;

            // Return raw pointer as opaque capsule
            return nb::capsule(geom.get(), "ON_Geometry*");
        })
    ;

    nb::class_<ObjectTable>(m, "ObjectTable")
        .def("__iter__", [](ObjectTable& self) {return self.Begin();}, nb::keep_alive<0, 1>())
        .def("max_index", &ObjectTable::MaxIndex)
        .def("add", &ObjectTable::Add)
        .def("delete_by_uuid", &ObjectTable::DeleteByUUID, nb::arg("object_uuid"))
    ;
}
