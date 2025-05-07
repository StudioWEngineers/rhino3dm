#pragma once

#include "opennurbs_includes.h"

class LayerView {
public:
    LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref);
    LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref, std::shared_ptr<ONX_Model>& model);
    ~LayerView();

    const ON_Layer* LayerHandle() const;

    static std::wstring PathSeparator();

    ON_UUID GetId() const;

    std::wstring GetName() const;

    std::wstring GetFullPath() const;

    ON_UUID GetParentLayerId() const;

    int GetIgesLevel() const;

    ON_Color GetColor() const;

    ON_Color GetPlotColor() const;

    double GetPlotWeight() const;

    int GetLinetypeIndex() const;

    int GetRenderMaterialIndex() const;

    bool IsVisible() const;

    bool IsLocked() const;

    bool GetPersistentVisibility() const;

    bool GetPersistentLocking() const;

    bool IsExpanded() const;

    const std::string ToString() const;

private:
    ON_Layer* m_layer = nullptr;
    std::shared_ptr<ONX_Model> m_model;
    ON_ModelComponentReference m_comp_ref;

    void SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref);
};
