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
    void SetIgesLevel(int level);
    void SetIsExpanded(bool is_expanded);
    void SetIsLocked(bool is_locked);
    void SetIsVisible(bool is_visible);
    void SetLinetypeIndex(int index);
    void SetName(const std::wstring& name);
    void SetParentLayerId(ON_UUID on_uuid);
    void SetPersistentLocking(bool persistent_locking);
    void SetPersistentVisibility(bool persistent_visibility);
    void SetPlotColor(const ON_Color& on_color);
    void SetPlotWeight(double weight);
    void SetRenderMaterialIndex(int index);

    const std::string ToString() const;

private:
    ON_ModelComponentReference m_comp_ref;
    ON_Layer* m_layer = nullptr;
    std::shared_ptr<ONX_Model> m_model;
};
