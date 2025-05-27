/*
    src/layer_table.h: Implementation details related to LayerTable.

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
    bool DeleteByName(std::wstring full_name);
    bool DeleteByUUID(ON_UUID on_uuid);
    const LayerView* GetByIndex(int index);
    const LayerView* GetByName(std::wstring full_name);
    const LayerView* GetByUUID(ON_UUID on_uuid);
    int GetLayerIndex(std::wstring full_name);
    const ON_UUID GetLayerUUID(std::wstring full_name);
    bool Has(std::wstring full_name);
    int MaxIndex() const;
    bool Replace(std::wstring full_name, Layer& new_layer);

    class Iterator {
    public:
        Iterator(LayerTable* table, int index);

        const LayerView* operator*() const;
        Iterator& operator++();
        bool IsOver() const;

    private:
        LayerTable* m_table;
        unsigned int m_index;
        unsigned int m_count;
    };

    Iterator Begin();

private:
    std::shared_ptr<ONX_Model> m_model;
};
