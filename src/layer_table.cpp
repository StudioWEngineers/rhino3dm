#include "layer.h"
#include "layer_table.h"
#include <iostream>

LayerTable::LayerTable(std::shared_ptr<ONX_Model> model) {
    m_model = model;
}

int LayerTable::Add(const Layer& layer) {
    ON_ModelComponentReference mr = m_model->AddModelComponent(*layer.LayerHandle());
    const ON_Layer *managed_layer = ON_Layer::FromModelComponentRef(mr, nullptr);

    return (nullptr != managed_layer) ? managed_layer->Index() : ON_UNSET_INT_INDEX;
}

int LayerTable::Count() const {
    return m_model.get()->ActiveComponentCount(ON_ModelComponent::Type::Layer);
}

const int LayerTable::GetLayerIndex(std::wstring full_name) {
    for (unsigned int i = 0; i < LayerTable::Count(); ++i) {
        if (full_name == LayerTable::GetByIndex(i)->GetFullPath()) {
            return i;
        }
    }
    return -1;
}

const ON_UUID LayerTable::GetLayerUUID(std::wstring full_name) {
    for (unsigned int i = 0; i < LayerTable::Count(); ++i) {
        if (full_name == LayerTable::GetByIndex(i)->GetFullPath()) {
            return LayerTable::GetByIndex(i)->GetLayerId();
        }
    }
    return ON_nil_uuid;
}

bool LayerTable::Replace(std::wstring layer_to_be_replaced, Layer& new_layer) {


    //ON_Layer* test_layer = new ON_Layer();
    const ON_Layer* test_layer = new_layer.LayerHandle();
    //test_layer->SetId(LayerTable::GetLayerUUID(layer_to_be_replaced));
    //test_layer->SetIndex(LayerTable::GetLayerIndex(layer_to_be_replaced));
    //test_layer->SetName(new_layer.GetName().c_str());

    if (!ON_UuidIsNotNil(LayerTable::GetLayerUUID(layer_to_be_replaced)) || LayerTable::GetLayerIndex(layer_to_be_replaced) < 0)
    return false;

    if (!LayerTable::DeleteByName(layer_to_be_replaced)) {
        return false;
    }
    //test_layer->SetColor(layer_to_be_replaced);

    ON_ModelComponent* mod_comp = ON_ModelComponent::Cast(const_cast<ON_Layer*>(test_layer));
    ON_ModelComponentReference comp_ref = m_model->AddModelComponentForExperts(mod_comp, true, false, false);
    return !comp_ref.IsEmpty();
}

bool LayerTable::Replace2(std::wstring layer_to_be_replaced, Layer& new_layer) {
    // Create a proper copy of the new layer to insert
    ON_Layer* replacement_layer = new ON_Layer();
    replacement_layer->SetName(new_layer.GetName().c_str());
    replacement_layer->SetColor(new_layer.GetColor());
    replacement_layer->SetLinetypeIndex(new_layer.GetLinetypeIndex());
    // Set any additional properties here
    if (!replacement_layer->SetId(LayerTable::GetLayerUUID(layer_to_be_replaced))) {
        return false;
    }
    if (!replacement_layer->SetIndex(LayerTable::GetLayerIndex(layer_to_be_replaced))) {
        return false;
    }

    if (!LayerTable::DeleteByName(layer_to_be_replaced)) {
        delete replacement_layer;
        return false;
    }

    ON_ModelComponent* mod_comp = ON_ModelComponent::Cast(replacement_layer);
    ON_ModelComponentReference comp_ref = m_model->AddModelComponentForExperts(mod_comp, true, false, false);

    return !comp_ref.IsEmpty();
}

bool LayerTable::DeleteById(ON_UUID on_uuid) {
    return !m_model->RemoveModelComponent(ON_ModelComponent::Type::Layer, on_uuid).IsEmpty();
}

bool LayerTable::DeleteByName(std::wstring layer_name) {
    const ON_UUID on_uuid = LayerTable::GetLayerUUID(layer_name);
    return !m_model->RemoveModelComponent(ON_ModelComponent::Type::Layer, on_uuid).IsEmpty();
}

const LayerView* LayerTable::GetByName(std::wstring full_name) {
    return GetByUUID(GetLayerUUID(full_name));
}

bool LayerTable::Has(std::wstring full_name) {
    const int num_layers = LayerTable::Count();
    for (int i = 0; i < num_layers; ++i) {
        const std::wstring name = LayerTable::GetByIndex(i)->GetFullPath();
        if (full_name == name) {
            return true;
        }
    }
    return false;
}

const LayerView* LayerTable::GetByIndex(int index) {
    ON_ModelComponentReference comp_ref = m_model->ComponentFromIndex(ON_ModelComponent::Type::Layer, index);
    if (comp_ref.IsEmpty()) {
        return nullptr;
    }
    ON_Layer* layer = const_cast<ON_Layer*>(ON_Layer::Cast(comp_ref.ModelComponent()));
    if (layer != nullptr) {
        return new LayerView(layer, &comp_ref, m_model);
    }
    return nullptr;
}

const LayerView* LayerTable::GetByUUID(ON_UUID on_uuid) {
    ON_ModelComponentReference comp_ref = m_model->ComponentFromId(ON_ModelComponent::Type::Layer, on_uuid);
    if (comp_ref.IsEmpty()) {
        return nullptr;
    }
    ON_Layer* layer = const_cast<ON_Layer*>(ON_Layer::Cast(comp_ref.ModelComponent()));
    if (layer != nullptr) {
        return new LayerView(layer, &comp_ref, m_model);
    }
    return nullptr;  // is this necessary?
}

LayerTable::Iterator LayerTable::Begin() {
    return Iterator(this, 0);
}

LayerTable::Iterator::Iterator(LayerTable* table, int index)
    : m_table(table), m_index(index), m_count(table->Count()) {}

bool LayerTable::Iterator::IsOver() const {
    return m_index >= m_count;
}

const LayerView* LayerTable::Iterator::operator*() const {
    return m_table->GetByIndex(m_index);
}

LayerTable::Iterator& LayerTable::Iterator::operator++() {
    ++m_index;
    return *this;
}
