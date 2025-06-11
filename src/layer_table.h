/*
    src/layer_table.h: Implementation details related to LayerTable.

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#pragma once

#include <memory>
#include "opennurbs_includes.h"


class LayerTable {
public:
    LayerTable(std::shared_ptr<ONX_Model> model);

    int Add(const ON_Layer& layer);
    int Count() const;
    bool DeleteByName(std::wstring full_name);
    bool DeleteByUUID(ON_UUID on_uuid);
    ON_Layer* GetByIndex(int index);
    ON_Layer* GetByName(std::wstring full_name);
    ON_Layer* GetByUUID(ON_UUID on_uuid);
    const std::wstring GetFullPath(const ON_Layer* layer) const;
    int GetLayerIndex(std::wstring full_name);
    const ON_UUID GetLayerUUID(std::wstring full_name);
    bool Has(std::wstring full_name);
    int MaxIndex() const;

    class Iterator {
    public:
        Iterator(LayerTable* table, int index);

        ON_Layer* operator*() const;
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
