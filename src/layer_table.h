#pragma once

#include "layer_view.h"
//#include "opennurbs_includes.h"


class BND_File3dmLayerTable {
    std::shared_ptr<ONX_Model> m_model;

public:
    BND_File3dmLayerTable(std::shared_ptr<ONX_Model> m);
    int Count() const;
    int Add(const class Layer &layer);
    bool Delete(ON_UUID id);
    bool Has(std::wstring full_name);
    const class LayerView *Get(std::wstring full_name);
    class LayerView *FindName(std::wstring name, ON_UUID parentId);
    class LayerView *FindIndex(int index);
    class LayerView *IterIndex(int index); // helper function for iterator
    class LayerView *FindId(ON_UUID id);
};
