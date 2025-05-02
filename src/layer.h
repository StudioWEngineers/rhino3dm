#pragma once

#include "bindings.h"

void LayerBindings(rh3dmpymodule& m);

class Layer {
public:
    ON_Layer* m_layer = nullptr;

    Layer();
    Layer(ON_Layer* layer, const ON_ModelComponentReference* compref);
    Layer(ON_Layer* layer, const ON_ModelComponentReference* compref, std::shared_ptr<ONX_Model>& model);
    ~Layer();

    //static std::wstring PathSeparator();

    std::wstring GetName() const;
    void SetName(const std::wstring& name);

    //std::wstring GetFullPath() const;

    //BND_UUID GetParentLayerId() const;
    //void SetParentLayerId(BND_UUID id);

    //int GetIgesLevel() const;
    //void SetIgesLevel(int level);

    //bool HasPerViewportSettings(BND_UUID viewportId) const;
    //void DeletePerViewportSettings(BND_UUID viewportId);

    //BND_Color GetColor() const;
    //void SetColor(const BND_Color& color);

    //BND_Color PerViewportColor(BND_UUID viewportId) const;
    //void SetPerViewportColor(BND_UUID viewportId, BND_Color color);
    //void DeletePerViewportColor(BND_UUID viewportId);

    //BND_Color GetPlotColor() const;
    //void SetPlotColor(const BND_Color& color);

    //double GetPlotWeight() const;
    //void SetPlotWeight(double weight);

    //int GetLinetypeIndex() const;
    //void SetLinetypeIndex(int index);

    //int GetRenderMaterialIndex() const;
    //void SetRenderMaterialIndex(int index);

    //bool IsVisible() const;
    //void SetVisible(bool visible);

    //bool IsLocked() const;
    //void SetLocked(bool locked);

    //bool GetPersistentVisibility() const;
    //void SetPersistentVisibility(bool persistent);
    //void UnsetPersistentVisibility();

    //bool GetPersistentLocking() const;
    //void SetPersistentLocking(bool persistent);
    //void UnsetPersistentLocking();

    //bool IsExpanded() const;
    //void SetExpanded(bool expanded);

protected:
    void SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref);

    std::shared_ptr<ONX_Model> m_model;
    ON_ModelComponentReference m_component_ref;
};
