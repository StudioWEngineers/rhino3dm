#include "bindings.h"
#include "../layer.h"
#include "../layer_table.h"
#include "uuid_caster.h"

namespace nb = nanobind;

void initLayerTableBindings(nanobind::module_ &m) {
    nb::class_<LayerTable::Iterator>(m, "LayerTableIterator")
    .def("__iter__", [](LayerTable::Iterator &it) -> LayerTable::Iterator& {
        return it;
    })
    .def("__next__", [](LayerTable::Iterator &it) {
        if (it.is_done()) {
            throw nb::stop_iteration();
        }
        LayerView* result = *it;
        ++it;
        return result;
    }, nb::rv_policy::take_ownership);

    nb::class_<LayerTable>(m, "LayerTable")
        .def("__len__", &LayerTable::Count)
        .def("__getitem__", &LayerTable::FindIndex)
        .def("Add", &LayerTable::Add, nb::arg("layer"))
        .def("delete_by_id", &LayerTable::DeleteById, nb::arg("uuid"))
        .def("FindName", &LayerTable::FindName, nb::arg("name"), nb::arg("parentId"))
        .def("FindIndex", &LayerTable::FindIndex, nb::arg("index"))
        .def("FindId", &LayerTable::FindId, nb::arg("id"))
        .def("has", &LayerTable::Has, "Return True if the layer is found, False otherwise.", nb::arg("full_name"))
        .def("get", &LayerTable::Get, "Return the immutable layer if it is found, raise IndexError otherwise.", nb::arg("full_name"))
        .def("__iter__", [](LayerTable &self) {
            return self.begin();
        }, nb::keep_alive<0, 1>())
    ;
}
