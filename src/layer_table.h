/*
    src/layer.h: Implementation details related to Layer.
    Rearranged from .../bnd_layer.h in https://github.com/mcneel/rhino3dm

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#pragma once

#include "layer.h"
#include "layer_view.h"


class LayerTable {
public:
    LayerTable(std::shared_ptr<ONX_Model> model);

    int Add(const Layer& layer);
    int Count() const;
    bool DeleteById(ON_UUID id);
    bool DeleteByName(std::wstring full_name);
    bool Has(std::wstring full_name);
    bool Replace(std::wstring full_name, Layer& new_layer);
    bool Replace2(std::wstring full_name, Layer& new_layer);

    const int GetLayerIndex(std::wstring full_name);
    const ON_UUID GetLayerUUID(std::wstring full_name);

    const LayerView* GetByName(std::wstring full_name);
    const LayerView* GetByIndex(int index);
    const LayerView* GetByUUID(ON_UUID on_uuid);

    class Iterator {
    public:
        Iterator(LayerTable* table, int index);

        const LayerView* operator*() const;
        Iterator& operator++();
        bool IsOver() const;

    private:
        LayerTable* m_table;
        std::size_t m_index;
        std::size_t m_count;
    };

    Iterator Begin();

private:
    std::shared_ptr<ONX_Model> m_model;
};
