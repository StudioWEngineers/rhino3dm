// src/bindings/layer_bindings.cpp
#include "layer_bindings.h"
#include "../layer.h"
//#include "uuid_conversion.h"
#include "uuid_caster.h"
#include "color_caster.h"

void LayerBindings(rh3dmpymodule& m) {
    py::class_<Layer>(m, "Layer")

        .def(py::init<>())

        .def("get_name", &Layer::GetName, "Returns the Layer's name.")
        .def("get_plot_color", &Layer::GetPlotColor, "Returns the Layer's plot color.")

        .def("set_name", &Layer::SetName, "Sets the Layer's name.", py::arg("name"))
        .def("set_plot_color", &Layer::SetPlotColor, "Sets the Layer's plot color.", py::arg("new_color"))

        .def("get_full_path", &Layer::GetFullPath, "Returns the full path to this Layer, including nesting information.")

        //.def("ParentLayerId", [](const Layer& self) {
        //    return ON_UUID_to_Binding(self.GetParentLayerId());
        //})

        .def_property("IgesLevel", &Layer::GetIgesLevel, &Layer::SetIgesLevel)

        .def("HasPerViewportSettings", &Layer::HasPerViewportSettings)

        .def("DeletePerViewportSettings", &Layer::DeletePerViewportSettings)

        .def("ParentLayerId", &Layer::GetParentLayerId);
}
