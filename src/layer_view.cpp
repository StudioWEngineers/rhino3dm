#include "layer_view.h"



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

bool LayerView::HasPerViewportSettings(ON_UUID viewportId) const
{
  return m_layer->HasPerViewportSettings(viewportId);
}

ON_Color LayerView::GetColor() const {
    return m_layer->Color();
}

ON_Color LayerView::PerViewportColor(ON_UUID viewportId) const {
  return m_layer->PerViewportColor(viewportId);
}

ON_Color LayerView::GetPlotColor() const {
  return m_layer->PlotColor();
}
