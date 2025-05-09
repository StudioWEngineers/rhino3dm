#include "../layer_view.h"
#include "color_caster.h"
#include "layer_view_bindings.h"
#include "uuid_caster.h"

namespace nb = nanobind;

void LayerViewBindings(nb::module_ &m) {
    nb::class_<LayerView>(m, "LayerView")
        .def("__repr__", &LayerView::ToString)

        .def_prop_ro("color", &LayerView::GetColor)
        .def_prop_ro("full_path", &LayerView::GetFullPath)
        .def_prop_ro("iges_level", &LayerView::GetIgesLevel)
        .def_prop_ro("is_expanded", &LayerView::GetIsExpanded)
        .def_prop_ro("is_locked", &LayerView::GetIsLocked)
        .def_prop_ro("is_visible", &LayerView::GetIsVisible)
        .def_prop_ro("layer_uuid", &LayerView::GetLayerId)
        .def_prop_ro("line_type_index", &LayerView::GetLinetypeIndex)
        .def_prop_ro("name", &LayerView::GetName)
        .def_prop_ro("parent_uuid", &LayerView::GetParentLayerId)
        .def_prop_ro("persistent_locking", &LayerView::GetPersistentLocking)
        .def_prop_ro("persistent_visibility", &LayerView::GetPersistentVisibility)
        .def_prop_ro("plot_color", &LayerView::GetPlotColor)
        .def_prop_ro("plot_weight", &LayerView::GetPlotWeight)
        .def_prop_ro("render_material_index", &LayerView::GetRenderMaterialIndex)

        .def_prop_ro_static("path_separator", &LayerView::GetPathSeparator)
    ;
}
