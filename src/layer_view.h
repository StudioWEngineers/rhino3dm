/*
    src/layer_view.h: Implementation details related to LayerView, a ON_Layer already
    added to the model.
    Rearranged from .../bnd_layer.h in https://github.com/mcneel/rhino3dm

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#pragma once

#include "opennurbs_includes.h"

class LayerView {
public:
    LayerView(ON_Layer* layer, const ON_ModelComponentReference* comp_ref);
    LayerView(ON_Layer* layer, const ON_ModelComponentReference* comp_ref, std::shared_ptr<ONX_Model>& model);
    ~LayerView();

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

    const std::string ToString() const;

private:
    ON_ModelComponentReference m_comp_ref;
    ON_Layer* m_layer = nullptr;
    std::shared_ptr<ONX_Model> m_model;

    void SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* comp_ref);
};
