#include "../model.h"
#include "bindings.h"
#include "model_bindings.h"


void ModelBindings(nb::module_& m) {

    nb::class_<Model>(m, "Model")

        /*magic methods*/
        .def(nb::init<>())

        /*other methods*/
        .def("new_revision", &Model::NewRevision)
        .def("read", &Model::Read)
        .def("reset", &Model::Reset)
        .def("write", &Model::Write, nb::arg("path_to_file"), nb::arg("version") = 7)

        /*read-write properties*/
        .def_prop_rw("application_details", &Model::GetApplicationDetails, &Model::SetApplicationDetails)
        .def_prop_rw("application_name", &Model::GetApplicationName, &Model::SetApplicationName)
        .def_prop_rw("application_url", &Model::GetApplicationUrl, &Model::SetApplicationUrl)
        .def_prop_rw("created_by", &Model::GetCreatedBy, &Model::SetCreatedBy)
        .def_prop_rw("last_edited_by", &Model::GetLastEditedBy, &Model::SetLastEditedBy)

        /*read-only properties*/
        .def_prop_ro("archive_version", &Model::GetArchiveVersion)
        .def_prop_ro("LayerTable", &Model::ModelLayerTable)
        .def_prop_ro("ObjectTable", &Model::ModelObjectTable)
        .def_prop_ro("revision", &Model::GetRevision)
    ;
}
