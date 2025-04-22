#include "bindings.h"



LayerView::LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref)
{
  SetTrackedPointer(layer, compref);
}

LayerView::LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref, std::shared_ptr<ONX_Model>& model)
{
  SetTrackedPointer(layer, compref);
  m_model = model;
}

LayerView::~LayerView()
{
  // m_component_ref should almost always track the lifetime of the ON_Object
  if (m_layer && m_component_ref.IsEmpty())
    delete m_layer;
}

void LayerView::SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref)
{

  if( compref )
  {
    m_component_ref = *compref;
  }
  else
  {
    ON_ModelComponent* model_component = ON_ModelComponent::Cast(layer);
    if (nullptr == model_component)
      model_component = ON_ModelGeometryComponent::CreateManaged(layer, nullptr, nullptr);
    if (model_component)
      m_component_ref = ON_ModelComponentReference::CreateForExperts(model_component, true);
  }
  m_layer = layer;
}

std::wstring LayerView::GetName() const {
    return std::wstring(m_layer->NameAsPointer());
}

std::wstring LayerView::GetFullPath() const
{
  ONX_Model* model = m_model.get();
  if (nullptr == model)
    return GetName();

  ON_wString fullPath = m_layer->Name();
  ON_UUID parent_id = m_layer->ParentId();
  while (ON_UuidIsNotNil(parent_id))
  {
    ON_ModelComponentReference compref = model->LayerFromId(parent_id);
    const ON_ModelComponent* model_component = compref.ModelComponent();
    ON_Layer* modellayer = const_cast<ON_Layer*>(ON_Layer::Cast(model_component));
    if (nullptr == modellayer)
      break;

    ON_wString parentName = modellayer->Name();
    fullPath = parentName + ON_ModelComponent::NamePathSeparator + fullPath;
    parent_id = modellayer->ParentId();
  }

  return std::wstring(fullPath.Array());
}

bool LayerView::HasPerViewportSettings(BND_UUID viewportId) const
{
  ON_UUID id = Binding_to_ON_UUID(viewportId);
  return m_layer->HasPerViewportSettings(id);
}

BND_Color LayerView::GetColor() const
{
    ON_Color c = m_layer->Color();
    return ON_Color_to_Binding(c);
}

BND_Color LayerView::PerViewportColor(BND_UUID viewportId) const
{
  ON_UUID id = Binding_to_ON_UUID(viewportId);
  ON_Color c = m_layer->PerViewportColor(id);
  return ON_Color_to_Binding(c);
}

BND_Color LayerView::GetPlotColor() const
{
  ON_Color c = m_layer->PlotColor();
  return ON_Color_to_Binding(c);
}


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
