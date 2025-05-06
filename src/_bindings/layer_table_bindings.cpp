#include "bindings.h"
#include "../layer.h"
#include "../layer_table.h"
#include "uuid_caster.h"


// --------------------- Iterator helpers ------- //
//template <typename IT>
//struct PyBNDIterator {
//    PyBNDIterator(const IT table, py::object ref)
//        : seq(table), ref(ref) {}
//
//    py::object next() {
//        if (index >= seq.Count())
//            throw py::stop_iteration();
//        LayerView* lv = const_cast<IT>(seq).IterIndex(index++);
//        //std::cout << typeid(*lv).name() << std::endl;
//        //static_assert(std::is_same_v<decltype(lv), LayerView*>, "Type mismatch!");
//        return py::cast(lv, py::rv_policy::reference);  // or take_ownership if appropriate
//        //return py::cast(reinterpret_cast<LayerView*>(lv), py::rv_policy::reference);
//    }
//
//    const IT seq;
//    py::object ref;
//    int index = 0;
//};

namespace py = nanobind;

void initLayerTableBindings(nanobind::module_ &m) {
    //using LayerIterator = PyBNDIterator<LayerTable &>;

    //py::class_<LayerIterator>(m, "__LayerIterator")
    //    .def("__iter__", [](LayerIterator &it) -> LayerIterator & {
    //        return it;
    //    })
    //    .def("__next__", &LayerIterator::next);

    py::class_<LayerTable>(m, "LayerTable")
        .def("__len__", &LayerTable::Count)
        .def("__getitem__", &LayerTable::FindIndex)
//#if !defined(NANOBIND)
//        .def("__iter__", [](py::object s) { return PyBNDIterator<LayerTable &, LayerView *>(s.cast<LayerTable &>(), s); })
//#endif
        //.def("__iter__", [](LayerTable &self) {
        //    return LayerIterator(self, py::cast(self, py::rv_policy::reference));
        //})
        .def("Add", &LayerTable::Add, py::arg("layer"))
        .def("delete_by_id", &LayerTable::DeleteById, py::arg("uuid"))
        .def("FindName", &LayerTable::FindName, py::arg("name"), py::arg("parentId"))
        .def("FindIndex", &LayerTable::FindIndex, py::arg("index"))
        .def("FindId", &LayerTable::FindId, py::arg("id"))
        .def("has", &LayerTable::Has, "Return True if the layer is found, False otherwise.", py::arg("full_name"))
        .def("get", &LayerTable::Get, "Return the immutable layer if it is found, raise IndexError otherwise.", py::arg("full_name"));
}
