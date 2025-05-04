#include "bindings.h"
#include "uuid_caster.h"
#include "color_caster.h"
#include "../layer_view.h"


void initLayerViewBindings(rh3dmpymodule& m) {
  py::class_<LayerView>(m, "LayerView")
    .def_property_readonly_static("PathSeparator", &LayerView::PathSeparator)
    .def_property_readonly("Name", &LayerView::GetName)
    .def_property_readonly("FullPath", &LayerView::GetFullPath)
    .def_property_readonly("Id", &LayerView::GetId)
    .def_property_readonly("Index", &LayerView::GetIndex)
    .def_property_readonly("ParentLayerId", &LayerView::GetParentLayerId)
    .def_property_readonly("IgesLevel", &LayerView::GetIgesLevel)
    .def("HasPerViewportSettings", &LayerView::HasPerViewportSettings, py::arg("viewportId"))
    .def_property_readonly("Color", &LayerView::GetColor)
    .def("PerViewportColor", &LayerView::PerViewportColor, py::arg("viewportId"))
    .def_property_readonly("PlotColor", &LayerView::GetPlotColor)
    .def_property_readonly("PlotWeight", &LayerView::GetPlotWeight)
    .def_property_readonly("LinetypeIndex", &LayerView::GetLinetypeIndex)
    .def_property_readonly("RenderMaterialIndex", &LayerView::GetRenderMaterialIndex)
    .def_property_readonly("Visible", &LayerView::IsVisible)
    .def_property_readonly("Locked", &LayerView::IsLocked)
    .def("GetPersistentVisibility", &LayerView::GetPersistentVisibility)
    .def("GetPersistentLocking", &LayerView::GetPersistentLocking)
    .def_property_readonly("Expanded", &LayerView::IsExpanded)
    ;
}
