/*
    src/layer.h: Implementation details related to Layer.
    Rearranged from .../bnd_layer.h in https://github.com/mcneel/rhino3dm

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#pragma once

#include "opennurbs_includes.h"


class Layer {
public:
    Layer();
    ~Layer();

    const ON_Layer* LayerHandle() const;

    ON_Color GetColor() const;
    std::wstring GetFullPath() const;
    int GetIgesLevel() const;
    bool GetIsExpanded() const;
    bool GetIsLocked() const;
    bool GetIsVisible() const;
    ON_UUID GetLayerId() const;
    int GetLinetypeIndex() const;
    std::wstring GetName() const;
    ON_UUID GetParentLayerId() const;
    static std::wstring GetPathSeparator();
    bool GetPersistentLocking() const;
    bool GetPersistentVisibility() const;
    ON_Color GetPlotColor() const;
    double GetPlotWeight() const;
    int GetRenderMaterialIndex() const;

    void SetColor(const ON_Color& on_color);
    void SetIgesLevel(const int level);
    void SetIsExpanded(const bool is_expanded);
    void SetIsLocked(const bool is_locked);
    void SetIsVisible(const bool is_visible);
    void SetLayerId(const ON_UUID on_uuid);
    void SetLinetypeIndex(const int index);
    void SetName(const std::wstring& name);
    void SetParentLayerId(const ON_UUID on_uuid);
    void SetPersistentLocking(const bool persistent_locking);
    void SetPersistentVisibility(const bool persistent_visibility);
    void SetPlotColor(const ON_Color& on_color);
    void SetPlotWeight(const double weight);
    void SetRenderMaterialIndex(const int index);

    const std::string ToString() const;

private:
    ON_ModelComponentReference m_comp_ref;
    ON_Layer* m_layer = nullptr;
    std::shared_ptr<ONX_Model> m_model;
};
