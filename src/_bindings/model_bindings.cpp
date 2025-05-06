#include "bindings.h"
//#include "base64.h"

#include "../model.h"

namespace py = nanobind;

void ModelBindings(rh3dmpymodule& m)
{


  py::class_<Model>(m, "File3dm")
    .def(py::init<>())
    .def_static("Read", &Model::Read, py::arg("path"))
    .def_static("ReadNotes", &Model::ReadNotes, py::arg("path"))
    .def_static("ReadArchiveVersion", &Model::ReadArchiveVersion, py::arg("path"))
//#if !defined(NANOBIND)
//    .def_static("FromByteArray", [](py::buffer b) {
//      py::buffer_info info = b.request();
//      return Model::FromByteArray(static_cast<int>(info.size), info.ptr);
//    })
// #endif
    .def("write", &Model::Write, py::arg("path"), py::arg("version")=7)
    .def_prop_ro("LayerTable", &Model::ModelLayerTable)
    ;
}
