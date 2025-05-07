#include "bindings.h"
//#include "base64.h"

#include "../model.h"

namespace nb = nanobind;

void ModelBindings(nanobind::module_ &m)
{


  nb::class_<Model>(m, "File3dm")
    .def(nb::init<>())
    .def_static("Read", &Model::Read, nb::arg("path"))
    .def_static("ReadNotes", &Model::ReadNotes, nb::arg("path"))
    .def_static("ReadArchiveVersion", &Model::ReadArchiveVersion, nb::arg("path"))
//#if !defined(NANOBIND)
//    .def_static("FromByteArray", [](nb::buffer b) {
//      nb::buffer_info info = b.request();
//      return Model::FromByteArray(static_cast<int>(info.size), info.ptr);
//    })
// #endif
    .def("write", &Model::Write, nb::arg("path"), nb::arg("version")=7)
    .def_prop_ro("LayerTable", &Model::ModelLayerTable)
    ;
}
