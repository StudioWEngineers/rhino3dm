#include "bindings.h"
#include "model_bindings.h"
#include "../model.h"


void ModelBindings(nb::module_& m) {
    nb::class_<Model>(m, "Model")
        .def(nb::init<>())

        .def("write", &Model::Write, nb::arg("path"), nb::arg("version")=7)

        .def_prop_ro("LayerTable", &Model::ModelLayerTable)
        .def_prop_ro("ObjectTable", &Model::ModelObjectTable)

        .def("read", &Model::Read, nb::arg("path"))
    ;
}
