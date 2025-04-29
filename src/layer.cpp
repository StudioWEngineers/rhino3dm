#include "bindings.h"

Layer::Layer()
{
  SetTrackedPointer(new ON_Layer(), nullptr);
}

Layer::Layer(ON_Layer* layer, const ON_ModelComponentReference* compref)
{
  SetTrackedPointer(layer, compref);
}

Layer::Layer(ON_Layer* layer, const ON_ModelComponentReference* compref, std::shared_ptr<ONX_Model>& model)
{
  SetTrackedPointer(layer, compref);
  m_model = model;
}

Layer::~Layer() {
  if (m_layer != nullptr && m_component_ref.IsEmpty()) {
    delete m_layer;
  }
}

void Layer::SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref)
{
  m_layer = layer;
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
  //BND_CommonObject::SetTrackedPointer(layer, compref);
}

//void BND_CommonObject::SetTrackedPointer(ON_Object* obj, const ON_ModelComponentReference* compref)
//{
//  if( compref )
//  {
//    m_component_ref = *compref;
//  }
//  else
//  {
//    ON_ModelComponent* model_component = ON_ModelComponent::Cast(obj);
//    if (nullptr == model_component)
//      model_component = ON_ModelGeometryComponent::CreateManaged(obj, nullptr, nullptr);
//    if (model_component)
//      m_component_ref = ON_ModelComponentReference::CreateForExperts(model_component, true);
//  }
//  m_object = obj;
//}

std::wstring Layer::GetFullPath() const
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

bool Layer::HasPerViewportSettings(BND_UUID viewportId) const
{
  ON_UUID id = Binding_to_ON_UUID(viewportId);
  return m_layer->HasPerViewportSettings(id);
}

void Layer::DeletePerViewportSettings(BND_UUID viewportId)
{
  ON_UUID id = Binding_to_ON_UUID(viewportId);
  m_layer->DeletePerViewportSettings(id);
}

BND_Color Layer::GetColor() const
{
  ON_Color c = m_layer->Color();
  return ON_Color_to_Binding(c);
}
void Layer::SetColor(const BND_Color& color)
{
  ON_Color c = Binding_to_ON_Color(color);
  m_layer->SetColor(c);
}

BND_Color Layer::PerViewportColor(BND_UUID viewportId) const
{
  ON_UUID id = Binding_to_ON_UUID(viewportId);
  ON_Color c = m_layer->PerViewportColor(id);
  return ON_Color_to_Binding(c);
}
void Layer::SetPerViewportColor(BND_UUID viewportId, BND_Color color)
{
  ON_UUID id = Binding_to_ON_UUID(viewportId);
  ON_Color c = Binding_to_ON_Color(color);
  m_layer->SetPerViewportColor(id, c);
}
void Layer::DeletePerViewportColor(BND_UUID viewportId)
{
  ON_UUID id = Binding_to_ON_UUID(viewportId);
  m_layer->DeletePerViewportColor(id);
}

BND_Color Layer::GetPlotColor() const
{
  ON_Color c = m_layer->PlotColor();
  return ON_Color_to_Binding(c);
}
void Layer::SetPlotColor(const BND_Color& color)
{
  ON_Color c = Binding_to_ON_Color(color);
  m_layer->SetPlotColor(c);
}

void LayerBindings(rh3dmpymodule& m)
{
  py::class_<Layer>(m, "Layer")
    .def(py::init<>())
    .def_property_readonly_static("PathSeparator", &Layer::PathSeparator)
    .def_property("Name", &Layer::GetName, &Layer::SetName)
    .def_property_readonly("FullPath", &Layer::GetFullPath)
    .def_property("Id", &Layer::GetId, &Layer::SetId)
    .def_property_readonly("Index", &Layer::GetIndex)
    .def_property("ParentLayerId", &Layer::GetParentLayerId, &Layer::SetParentLayerId)
    .def_property("IgesLevel", &Layer::GetIgesLevel, &Layer::SetIgesLevel)
    .def("HasPerViewportSettings", &Layer::HasPerViewportSettings, py::arg("viewportId"))
    .def("DeletePerViewportSettings", &Layer::DeletePerViewportSettings, py::arg("viewportId"))
    .def_property("Color", &Layer::GetColor, &Layer::SetColor)
    .def("PerViewportColor", &Layer::PerViewportColor, py::arg("viewportId"))
    .def("SetPerViewportColor", &Layer::SetPerViewportColor, py::arg("viewportId"), py::arg("color"))
    .def("DeletePerViewportColor", &Layer::DeletePerViewportColor, py::arg("viewportId"))
    .def_property("PlotColor", &Layer::GetPlotColor, &Layer::SetPlotColor)
    .def_property("PlotWeight", &Layer::GetPlotWeight, &Layer::SetPlotWeight)
    .def_property("LinetypeIndex", &Layer::GetLinetypeIndex, &Layer::SetLinetypeIndex)
    .def_property("RenderMaterialIndex", &Layer::GetRenderMaterialIndex, &Layer::SetRenderMaterialIndex)
    .def_property("Visible", &Layer::IsVisible, &Layer::SetVisible)
    .def_property("Locked", &Layer::IsLocked, &Layer::SetLocked)
    .def("GetPersistentVisibility", &Layer::GetPersistentVisibility)
    .def("SetPersistentVisibility", &Layer::SetPersistentVisibility, py::arg("persistentVisibility"))
    .def("UnsetPersistentVisibility", &Layer::UnsetPersistentVisibility)
    .def("GetPersistentLocking", &Layer::GetPersistentLocking)
    .def("SetPersistentLocking", &Layer::SetPersistentLocking, py::arg("persistentLocking"))
    .def("UnsetPersistentLocking", &Layer::UnsetPersistentLocking)
    .def_property("Expanded", &Layer::IsExpanded, &Layer::SetExpanded)
    ;
}
