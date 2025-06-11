#include "layer_table.h"


LayerTable::LayerTable(std::shared_ptr<ONX_Model> model) {
    m_model = model;
}

int LayerTable::Add(const ON_Layer& layer) {
    const ON_Layer* m_layer = ON_Layer::FromModelComponentRef(m_model->AddModelComponent(layer), nullptr);

    return (nullptr != m_layer) ? m_layer->Index() : ON_UNSET_INT_INDEX;
}

int LayerTable::Count() const {
    return m_model.get()->ActiveComponentCount(ON_ModelComponent::Type::Layer);
}

bool LayerTable::DeleteByName(std::wstring layer_name) {
    return LayerTable::DeleteByUUID(LayerTable::GetLayerUUID(layer_name));
}

bool LayerTable::DeleteByUUID(ON_UUID on_uuid) {
    return !m_model->RemoveModelComponent(ON_ModelComponent::Type::Layer, on_uuid).IsEmpty();
}

ON_Layer* LayerTable::GetByIndex(int index) {
    ON_ModelComponentReference comp_ref = m_model->ComponentFromIndex(ON_ModelComponent::Type::Layer, index);
    if (comp_ref.IsEmpty()) {
        return nullptr;
    }

    ON_Layer* layer = const_cast<ON_Layer*>(ON_Layer::Cast(comp_ref.ModelComponent()));
    return layer;
}

ON_Layer* LayerTable::GetByName(std::wstring full_name) {
    return LayerTable::GetByUUID(LayerTable::GetLayerUUID(full_name));
}

ON_Layer* LayerTable::GetByUUID(ON_UUID on_uuid) {
    ON_ModelComponentReference comp_ref = m_model->ComponentFromId(ON_ModelComponent::Type::Layer, on_uuid);
    if (comp_ref.IsEmpty()) {
        return nullptr;
    }

    ON_Layer* layer = const_cast<ON_Layer*>(ON_Layer::Cast(comp_ref.ModelComponent()));
    return layer;
}

const std::wstring LayerTable::GetFullPath(const ON_Layer* layer) const {
    ONX_Model* model = m_model.get();
    if (model == nullptr) {
        return layer->NameAsPointer();
    }

    ON_wString full_name = layer->Name();
    ON_UUID parent_id = layer->ParentId();
    while (ON_UuidIsNotNil(parent_id)) {
        ON_ModelComponentReference comp_ref = model->LayerFromId(parent_id);
        const ON_Layer* layer = ON_Layer::Cast(comp_ref.ModelComponent());
        if (layer == nullptr) {
            break;
        }

        ON_wString parent_name = layer->Name();
        full_name = parent_name + ON_ModelComponent::NamePathSeparator + full_name;
        parent_id = layer->ParentId();
    }

    return std::wstring(full_name.Array());
}

int LayerTable::GetLayerIndex(std::wstring full_name) {
    const int max_index = m_model->Manifest().ComponentIndexLimit(ON_ModelComponent::Type::Layer);

    for (unsigned int i = 0; i < max_index; ++i) {
        ON_ModelComponentReference comp_ref = m_model->ComponentFromIndex(ON_ModelComponent::Type::Layer, i);
        if (comp_ref.IsEmpty())
            continue;

        const ON_Layer* layer = ON_Layer::Cast(comp_ref.ModelComponent());
        if (layer == nullptr) {
            continue;
        }

        if (full_name == LayerTable::GetFullPath(LayerTable::GetByIndex(i))) {
            return layer->Index();
        }
    }

    return ON_UNSET_INT_INDEX;
}

const ON_UUID LayerTable::GetLayerUUID(std::wstring full_name) {
    const int count = m_model->Manifest().ComponentIndexLimit(ON_ModelComponent::Type::Layer);

    for (unsigned int i = 0; i < count; ++i) {
        ON_ModelComponentReference comp_ref = m_model->ComponentFromIndex(ON_ModelComponent::Type::Layer, i);
        if (comp_ref.IsEmpty())
            continue;

        const ON_Layer* layer = ON_Layer::Cast(comp_ref.ModelComponent());
        if (!layer)
            continue;

        if (full_name == std::wstring(layer->Name())) {
            return layer->Id();
        }
    }

    return ON_nil_uuid;
}

bool LayerTable::Has(std::wstring full_name) {
    const int max_index = m_model->Manifest().ComponentIndexLimit(ON_ModelComponent::Type::Layer);

    for (unsigned int i = 0; i < max_index; ++i) {
        ON_ModelComponentReference comp_ref = m_model->ComponentFromIndex(ON_ModelComponent::Type::Layer, i);
        if (comp_ref.IsEmpty()) {
            continue;
        }

        const ON_Layer* layer = ON_Layer::Cast(comp_ref.ModelComponent());
        if (layer == nullptr)
            continue;

        if (full_name == layer->Name().Array()) {
            return true;
        }

        ON_wString name = layer->Name();
        ON_UUID parent_uuid = layer->ParentId();
        while (ON_UuidIsNotNil(parent_uuid)) {
            ON_ModelComponentReference comp_ref = m_model->LayerFromId(parent_uuid);
            ON_Layer* layer = const_cast<ON_Layer*>(ON_Layer::Cast(comp_ref.ModelComponent()));
            if (layer == nullptr) {
                break;
            }

            ON_wString parent_name = layer->Name();
            name = parent_name + ON_ModelComponent::NamePathSeparator + name;
            parent_uuid = layer->ParentId();
        }

        if (full_name == name.Array()) {
            return true;
        }

    }

    return false;
}

int LayerTable::MaxIndex() const {
    return m_model->Manifest().ComponentIndexLimit(ON_ModelComponent::Type::Layer);
}

LayerTable::Iterator::Iterator(LayerTable* table, int index)
    : m_table(table), m_index(index), m_count(table->MaxIndex()) {}

ON_Layer* LayerTable::Iterator::operator*() const {
    return m_table->GetByIndex(m_index);
}

LayerTable::Iterator& LayerTable::Iterator::operator++() {
    ++m_index;
    return *this;
}

bool LayerTable::Iterator::IsOver() const {
    return m_index >= m_count;
}

LayerTable::Iterator LayerTable::Begin() {
    return Iterator(this, 0);
}
