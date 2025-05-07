#include "bindings.h"
#include "../layer.h"
#include "../layer_table.h"
#include "uuid_caster.h"

namespace py = nanobind;

void initLayerTableBindings(nanobind::module_ &m) {
    py::class_<LayerTable::Iterator>(m, "LayerTableIterator")
    .def("__iter__", [](LayerTable::Iterator &it) -> LayerTable::Iterator& {
        return it;
    })
    .def("__next__", [](LayerTable::Iterator &it) {
        if (it.is_done()) {
            throw py::stop_iteration();
        }
        LayerView* result = *it;
        ++it;
        return result;
    }, py::rv_policy::take_ownership);

    py::class_<LayerTable>(m, "LayerTable")
        .def("__len__", &LayerTable::Count)
        .def("__getitem__", &LayerTable::FindIndex)
        .def("Add", &LayerTable::Add, py::arg("layer"))
        .def("delete_by_id", &LayerTable::DeleteById, py::arg("uuid"))
        .def("FindName", &LayerTable::FindName, py::arg("name"), py::arg("parentId"))
        .def("FindIndex", &LayerTable::FindIndex, py::arg("index"))
        .def("FindId", &LayerTable::FindId, py::arg("id"))
        .def("has", &LayerTable::Has, "Return True if the layer is found, False otherwise.", py::arg("full_name"))
        .def("get", &LayerTable::Get, "Return the immutable layer if it is found, raise IndexError otherwise.", py::arg("full_name"))
        .def("__iter__", [](LayerTable &self) {
            return self.begin();
        }, py::keep_alive<0, 1>())
    ;
}
