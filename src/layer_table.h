/*
    src/layer.h: Implementation details related to Layer.
    Rearranged from .../bnd_layer.h in https://github.com/mcneel/rhino3dm

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#pragma once

#include "layer_view.h"


class LayerTable {
public:
    LayerTable(std::shared_ptr<ONX_Model> m);

    int Add(const class Layer &layer);
    int Count() const;
    bool DeleteById(ON_UUID id);
    bool DeleteByName(std::wstring full_name);
    bool Has(std::wstring full_name);

    const LayerView* GetByName(std::wstring full_name);
    const LayerView* FindIndex(int index);
    const LayerView* FindId(ON_UUID id);

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
