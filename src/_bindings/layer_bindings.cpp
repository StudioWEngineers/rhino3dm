#include "layer_bindings.h"
#include "../layer.h"
#include "uuid_caster.h"
#include "color_caster.h"

namespace py = nanobind;

void LayerBindings(rh3dmpymodule& m) {
    py::class_<Layer>(m, "Layer")

        .def(py::init<>())

        .def("get_name", &Layer::GetName, "Returns the Layer's name.")
        .def("get_plot_color", &Layer::GetPlotColor, "Returns the Layer's plot color.")

        .def("set_name", &Layer::SetName, "Sets the Layer's name.", py::arg("name"))
        .def("set_plot_color", &Layer::SetPlotColor, "Sets the Layer's plot color.", py::arg("new_color"))

        .def("get_full_path", &Layer::GetFullPath, "Returns the full path to this Layer, including nesting information.")

        .def_prop_rw("iges_level", &Layer::GetIgesLevel, &Layer::SetIgesLevel)

        .def("get_parent_layer_id", &Layer::GetParentLayerId);
}
