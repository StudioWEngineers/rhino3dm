#pragma once
#include "opennurbs_includes.h"
#include <memory>
#include <string>

class Layer {
public:
    ON_Layer* m_layer = nullptr;

    Layer();
    ~Layer();

    static std::wstring PathSeparator();

    std::wstring GetName() const;
    void SetName(const std::wstring& name);

    std::wstring GetFullPath() const;

    ON_UUID GetParentLayerId() const;
    void SetParentLayerId(ON_UUID on_uuid);

    int GetIgesLevel() const;
    void SetIgesLevel(int level);

    ON_Color GetColor() const;
    void SetColor(const ON_Color& on_color);

    ON_Color GetPlotColor() const;
    void SetPlotColor(const ON_Color& on_color);

    double GetPlotWeight() const;
    void SetPlotWeight(double weight);

    int GetLinetypeIndex() const;
    void SetLinetypeIndex(int index);

    int GetRenderMaterialIndex() const;
    void SetRenderMaterialIndex(int index);

    bool IsVisible() const;
    void SetVisible(bool is_visible);

    bool IsLocked() const;
    void SetLocked(bool is_locked);

    bool GetPersistentVisibility() const;
    void SetPersistentVisibility(bool persistent_visibility);
    void UnsetPersistentVisibility();

    bool GetPersistentLocking() const;
    void SetPersistentLocking(bool persistent_locking);
    void UnsetPersistentLocking();

    bool IsExpanded() const;
    void SetExpanded(bool is_expanded);

protected:
    std::shared_ptr<ONX_Model> m_model;
    ON_ModelComponentReference m_component_ref;

private:
    void SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref);
};
