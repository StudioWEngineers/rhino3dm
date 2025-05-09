#include "layer.h"
#include "layer_table.h"

LayerTable::LayerTable(std::shared_ptr<ONX_Model> m) {
    m_model = m;
}

int LayerTable::Add(const Layer &layer) {
    ON_ModelComponentReference mr = m_model->AddModelComponent(*layer.LayerHandle());
    const ON_Layer *managed_layer = ON_Layer::FromModelComponentRef(mr, nullptr);

    return (nullptr != managed_layer) ? managed_layer->Index() : ON_UNSET_INT_INDEX;
}

int LayerTable::Count() const {
    return m_model.get()->ActiveComponentCount(ON_ModelComponent::Type::Layer);
}

bool LayerTable::DeleteById(ON_UUID on_uuid) {
    return !m_model->RemoveModelComponent(ON_ModelComponent::Type::Layer, on_uuid).IsEmpty();
}

const LayerView *LayerTable::GetByName(std::wstring full_name) {
    const int num_layers = LayerTable::Count();
    for (int i = 0; i <= num_layers; ++i) {  // should be < not <= -> check rhino docs
        const std::wstring name = LayerTable::FindIndex(i)->GetFullPath();
        if (full_name == name) {
            ON_ModelComponentReference cr = m_model->ComponentFromIndex(ON_ModelComponent::Type::Layer, i);
            ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(cr.ModelComponent()));
            return new LayerView(modellayer, &cr, m_model);
        }
    }
    return nullptr;
}

bool LayerTable::Has(std::wstring full_name) {
    const int num_layers = LayerTable::Count();
    for (int i = 0; i <= num_layers; ++i) {
        const std::wstring name = LayerTable::FindIndex(i)->GetFullPath();
        if (full_name == name) {
            return true;
        }
    }
    return false;
}

const LayerView *LayerTable::FindIndex(int index) {
    ON_ModelComponentReference compref = m_model->LayerFromIndex(index);
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);

    return nullptr;
}

const LayerView *LayerTable::FindId(ON_UUID id) {
    ON_ModelComponentReference compref = m_model->LayerFromId(id);
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);
    return nullptr;
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
    return m_table->FindIndex(m_index);
}

LayerTable::Iterator& LayerTable::Iterator::operator++() {
    ++m_index;
    return *this;
}
