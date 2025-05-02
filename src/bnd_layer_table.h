#include "bindings.h"
#include "layer_view.h"

#pragma once

void initLayerTableBindings(rh3dmpymodule &m);

class BND_File3dmLayerTable {
    std::shared_ptr<ONX_Model> m_model;

public:
    BND_File3dmLayerTable(std::shared_ptr<ONX_Model> m);
    int Count() const;
    int Add(const class Layer &layer);
    bool Delete(BND_UUID id);
    bool Has(std::wstring full_name);
    const class LayerView *Get(std::wstring full_name);
    class LayerView *FindName(std::wstring name, BND_UUID parentId);
    class LayerView *FindIndex(int index);
    class LayerView *IterIndex(int index); // helper function for iterator
    class LayerView *FindId(BND_UUID id);
};
