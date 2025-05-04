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

void initLayerTableBindings(rh3dmpymodule &m) {
    //using LayerIterator = PyBNDIterator<BND_File3dmLayerTable &>;

    //py::class_<LayerIterator>(m, "__LayerIterator")
    //    .def("__iter__", [](LayerIterator &it) -> LayerIterator & {
    //        return it;
    //    })
    //    .def("__next__", &LayerIterator::next);

    py::class_<BND_File3dmLayerTable>(m, "LayerTable")
        .def("__len__", &BND_File3dmLayerTable::Count)
        .def("__getitem__", &BND_File3dmLayerTable::FindIndex)
//#if !defined(NANOBIND)
//        .def("__iter__", [](py::object s) { return PyBNDIterator<BND_File3dmLayerTable &, LayerView *>(s.cast<BND_File3dmLayerTable &>(), s); })
//#endif
        //.def("__iter__", [](BND_File3dmLayerTable &self) {
        //    return LayerIterator(self, py::cast(self, py::rv_policy::reference));
        //})
        .def("Add", &BND_File3dmLayerTable::Add, py::arg("layer"))
        .def("Delete", &BND_File3dmLayerTable::Delete, py::arg("id"))
        .def("FindName", &BND_File3dmLayerTable::FindName, py::arg("name"), py::arg("parentId"))
        .def("FindIndex", &BND_File3dmLayerTable::FindIndex, py::arg("index"))
        .def("FindId", &BND_File3dmLayerTable::FindId, py::arg("id"))
        .def("has", &BND_File3dmLayerTable::Has, "Return True if the layer is found, False otherwise.", py::arg("full_name"))
        .def("get", &BND_File3dmLayerTable::Get, "Return the immutable layer if it is found, raise IndexError otherwise.", py::arg("full_name"));
}
