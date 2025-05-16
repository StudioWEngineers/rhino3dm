#include "bindings.h"
#include "../layer.h"
#include "../layer_table.h"
#include "uuid_caster.h"

namespace nb = nanobind;

void LayerTableBindings(nanobind::module_& m) {
    nb::class_<LayerTable::Iterator>(m, "__LayerTableIterator")
        .def("__iter__", [](LayerTable::Iterator &it) -> LayerTable::Iterator& {
            return it;
        })
        .def("__next__", [](LayerTable::Iterator &it) {
            while (!it.IsOver()) {
                const LayerView* result = *it;
                ++it;

                if (result != nullptr) {
                    return result;
                }
            }
            throw nb::stop_iteration();
            }, nb::rv_policy::take_ownership)
    ;

    nb::class_<LayerTable>(m, "LayerTable")
        .def("__len__", &LayerTable::Count)
        .def("__getitem__", &LayerTable::GetByIndex)
        .def("__iter__", [](LayerTable &self) {
            return self.Begin();
        }, nb::keep_alive<0, 1>())

        .def("add", &LayerTable::Add, nb::arg("layer"))
        .def("delete_by_id", &LayerTable::DeleteById, nb::arg("layer_uuid"))
        .def("delete_by_name", &LayerTable::DeleteByName, nb::arg("full_name"))
        .def("get_by_index", &LayerTable::GetByIndex, nb::arg("index"))
        .def("get_by_name", &LayerTable::GetByName, "Return the immutable layer if it is found, raise IndexError otherwise.", nb::arg("full_name"))
        .def("get_by_uuid", &LayerTable::GetByUUID, nb::arg("layer_uuid"))
        .def("get_layer_index", &LayerTable::GetLayerIndex, nb::arg("full_name"))
        .def("get_layer_uuid", &LayerTable::GetLayerUUID, nb::arg("full_name"))
        .def("has", &LayerTable::Has, "Return True if the layer is found, False otherwise.", nb::arg("full_name"))
        .def("replace", &LayerTable::Replace2, nb::arg("layer_to_be_replaced"), nb::arg("new_layer"))
    ;
}
