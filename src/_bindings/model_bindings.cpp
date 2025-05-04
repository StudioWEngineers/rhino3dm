#include "bindings.h"
//#include "base64.h"

#include "../model.h"

void ModelBindings(rh3dmpymodule& m)
{


  py::class_<BND_ONXModel>(m, "File3dm")
    .def(py::init<>())
    .def_static("Read", &BND_ONXModel::Read, py::arg("path"))
    .def_static("ReadNotes", &BND_ONXModel::ReadNotes, py::arg("path"))
    .def_static("ReadArchiveVersion", &BND_ONXModel::ReadArchiveVersion, py::arg("path"))
//#if !defined(NANOBIND)
//    .def_static("FromByteArray", [](py::buffer b) {
//      py::buffer_info info = b.request();
//      return BND_ONXModel::FromByteArray(static_cast<int>(info.size), info.ptr);
//    })
// #endif
    .def("write", &BND_ONXModel::Write, py::arg("path"), py::arg("version")=7)
    .def_property_readonly("LayerTable", &BND_ONXModel::LayerTable)
    ;
}
