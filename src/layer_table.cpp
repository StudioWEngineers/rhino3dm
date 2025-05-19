#include "layer.h"
#include "layer_table.h"


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

bool LayerTable::DeleteByName(std::wstring layer_name) {
    return LayerTable::DeleteByUUID(LayerTable::GetLayerUUID(layer_name));
}

bool LayerTable::DeleteByUUID(ON_UUID on_uuid) {
    return !m_model->RemoveModelComponent(ON_ModelComponent::Type::Layer, on_uuid).IsEmpty();
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

const LayerView* LayerTable::GetByName(std::wstring full_name) {
    return LayerTable::GetByUUID(LayerTable::GetLayerUUID(full_name));
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
    return nullptr;
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

        if (full_name == LayerTable::GetByIndex(i)->GetFullPath()) {
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

bool LayerTable::Replace(std::wstring layer_to_be_replaced, Layer& new_layer) {
    ON_Layer* replacement_layer = new ON_Layer();
    replacement_layer->SetColor(new_layer.GetColor());
    replacement_layer->SetIgesLevel(new_layer.GetIgesLevel());
    replacement_layer->m_bExpanded = new_layer.GetIsExpanded();
    replacement_layer->SetLocked(new_layer.GetIsLocked());
    replacement_layer->SetVisible(new_layer.GetIsVisible());
    replacement_layer->SetLinetypeIndex(new_layer.GetLinetypeIndex());
    replacement_layer->SetName(new_layer.GetName().c_str());
    replacement_layer->SetPersistentLocking(new_layer.GetPersistentLocking());
    replacement_layer->SetPersistentVisibility(new_layer.GetPersistentVisibility());
    replacement_layer->SetPlotColor(new_layer.GetPlotColor());
    replacement_layer->SetPlotWeight(new_layer.GetPlotWeight());
    replacement_layer->SetRenderMaterialIndex(new_layer.GetRenderMaterialIndex());

    if (!replacement_layer->SetId(LayerTable::GetLayerUUID(layer_to_be_replaced))) {
        delete replacement_layer;
        return false;
    }

    if (!replacement_layer->SetIndex(LayerTable::GetLayerIndex(layer_to_be_replaced))) {
        delete replacement_layer;
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

LayerTable::Iterator::Iterator(LayerTable* table, int index)
    : m_table(table), m_index(index), m_count(table->MaxIndex()) {}

const LayerView* LayerTable::Iterator::operator*() const {
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
