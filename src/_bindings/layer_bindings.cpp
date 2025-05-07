#include "../layer.h"
#include "color_caster.h"
#include "layer_bindings.h"
#include "uuid_caster.h"

namespace nb = nanobind;

void LayerBindings(nanobind::module_ &m) {
    nb::class_<Layer>(m, "Layer")
        .def(nb::init<>())
        .def("__repr__", &Layer::ToString)

        .def_prop_ro("full_path", &Layer::GetFullPath)

        .def_prop_ro_static("path_separator", &Layer::PathSeparator)

        .def_prop_rw("color", &Layer::GetColor, &Layer::SetColor)
        .def_prop_rw("iges_level", &Layer::GetIgesLevel, &Layer::SetIgesLevel)
        .def_prop_rw("is_expanded", &Layer::IsExpanded, &Layer::SetExpanded)
        .def_prop_rw("is_locked", &Layer::IsLocked, &Layer::SetLocked)
        .def_prop_rw("is_visible", &Layer::IsVisible, &Layer::SetVisible)
        .def_prop_rw("line_type_index", &Layer::GetLinetypeIndex, &Layer::SetLinetypeIndex)
        .def_prop_rw("name", &Layer::GetName, &Layer::SetName)
        .def_prop_rw("parent_uuid", &Layer::GetParentLayerId, &Layer::SetParentLayerId)
        .def_prop_rw("persistent_locking", &Layer::GetPersistentLocking, &Layer::SetPersistentLocking)
        .def_prop_rw("persistent_visibility", &Layer::GetPersistentVisibility, &Layer::SetPersistentVisibility)
        .def_prop_rw("plot_color", &Layer::GetPlotColor, &Layer::SetPlotColor)
        .def_prop_rw("plot_weight", &Layer::GetPlotWeight, &Layer::SetPlotWeight)
        .def_prop_rw("render_material_index", &Layer::GetRenderMaterialIndex, &Layer::SetRenderMaterialIndex)
    ;
}
