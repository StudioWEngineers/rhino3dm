#include "bindings.h"

#pragma once

void initLayerTableBindings(rh3dmpymodule &m);

class BND_File3dmLayerTable {
    std::shared_ptr<ONX_Model> m_model;

public:
    BND_File3dmLayerTable(std::shared_ptr<ONX_Model> m); // { m_model = m; }
    int Count() const;                                   //{ return m_model.get()->ActiveComponentCount(ON_ModelComponent::Type::Layer); }
    int Add(const class BND_Layer &layer);
    //int AddLayer(std::wstring name, BND_Color color);
    bool Delete(BND_UUID id);
    bool Has(std::wstring full_name);
    const class LayerView *Get(std::wstring full_name);
    class LayerView *FindName(std::wstring name, BND_UUID parentId);
    // BND_Layer* FindNameHash(NameHash nameHash)
    class LayerView *FindIndex(int index);
    class LayerView *IterIndex(int index); // helper function for iterator
    class LayerView *FindId(BND_UUID id);
};
