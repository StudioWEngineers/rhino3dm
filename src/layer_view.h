#include "bindings.h"

#pragma once

void initLayerViewBindings(rh3dmpymodule& m);

class LayerView {
  public:
    ON_Layer* m_layer = nullptr;
    std::shared_ptr<ONX_Model> m_model;
    LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref);
    LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref, std::shared_ptr<ONX_Model>& model);
    virtual ~LayerView();
    static std::wstring PathSeparator() { return std::wstring(ON_ModelComponent::NamePathSeparator.Array()); }

    std::wstring GetName() const;
    std::wstring GetFullPath() const;
    BND_UUID GetId() const { return ON_UUID_to_Binding(m_layer->Id()); }

    int GetIndex() const { return m_layer->Index(); }
    BND_UUID GetParentLayerId() const { return ON_UUID_to_Binding(m_layer->ParentId()); }
    int GetIgesLevel() const { return m_layer->IgesLevel(); }
    bool HasPerViewportSettings(BND_UUID viewportId) const;
    BND_Color GetColor() const;
    BND_Color PerViewportColor(BND_UUID viewportId) const;
    BND_Color GetPlotColor() const;
    double GetPlotWeight() const { return m_layer->PlotWeight(); }
    int GetLinetypeIndex() const { return m_layer->LinetypeIndex(); }
    int GetRenderMaterialIndex() const { return m_layer->RenderMaterialIndex(); }
    bool IsVisible() const { return m_layer->IsVisible(); }
    bool IsLocked() const { return m_layer->IsLocked(); }
    bool GetPersistentVisibility() const { return m_layer->PersistentVisibility(); }
    bool GetPersistentLocking() const { return m_layer->PersistentLocking(); }
    bool IsExpanded() const { return m_layer->m_bExpanded; }

  protected:
    ON_ModelComponentReference m_component_ref; // holds shared pointer for this class
    void SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref);
};
