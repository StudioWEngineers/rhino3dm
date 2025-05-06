#include "bindings.h"
#include "uuid_caster.h"
#include "color_caster.h"
#include "../layer_view.h"

namespace py = nanobind;

void initLayerViewBindings(nanobind::module_ &m) {
    py::class_<LayerView>(m, "LayerView")
        .def_prop_ro_static("PathSeparator", &LayerView::PathSeparator)
        .def_prop_ro("Name", &LayerView::GetName)
        .def_prop_ro("FullPath", &LayerView::GetFullPath)
        .def_prop_ro("Id", &LayerView::GetId)
        .def_prop_ro("Index", &LayerView::GetIndex)
        .def_prop_ro("ParentLayerId", &LayerView::GetParentLayerId)
        .def_prop_ro("IgesLevel", &LayerView::GetIgesLevel)
        .def("HasPerViewportSettings", &LayerView::HasPerViewportSettings, py::arg("viewportId"))
        .def_prop_ro("Color", &LayerView::GetColor)
        .def("PerViewportColor", &LayerView::PerViewportColor, py::arg("viewportId"))
        .def_prop_ro("PlotColor", &LayerView::GetPlotColor)
        .def_prop_ro("PlotWeight", &LayerView::GetPlotWeight)
        .def_prop_ro("LinetypeIndex", &LayerView::GetLinetypeIndex)
        .def_prop_ro("RenderMaterialIndex", &LayerView::GetRenderMaterialIndex)
        .def_prop_ro("Visible", &LayerView::IsVisible)
        .def_prop_ro("Locked", &LayerView::IsLocked)
        .def("GetPersistentVisibility", &LayerView::GetPersistentVisibility)
        .def("GetPersistentLocking", &LayerView::GetPersistentLocking)
        .def_prop_ro("Expanded", &LayerView::IsExpanded)
        ;
}
