#include "object_table.h"


ObjectTable::ObjectTable(std::shared_ptr<ONX_Model> model) {
    m_model = model;
}

bool ObjectTable::DeleteByUUID(ON_UUID on_uuid) {
    return !m_model->RemoveModelComponent(ON_ModelComponent::Type::ModelGeometry, on_uuid).IsEmpty();
}

int ObjectTable::MaxIndex() const {
    return m_model->Manifest().ComponentIndexLimit(ON_ModelComponent::Type::ModelGeometry);
}

ON_UUID ObjectTable::Add(const double x, const double y, const double z) const {
    if (m_model == nullptr) {
        return ON_nil_uuid;
    }

    ON_Point point_geometry(x, y, z);
    //const ON_3dmObjectAttributes* attr = attributes ? attributes->m_attributes : nullptr;

    ON_ModelComponentReference model_component_reference = m_model->AddModelGeometryComponent(&point_geometry, nullptr);
    return ON_ModelGeometryComponent::FromModelComponentRef(model_component_reference, &ON_ModelGeometryComponent::Unset)->Id();
}


// Iterator implementation

ObjectTable::Iterator::Iterator(ObjectTable* table)
    : m_table(table),
      m_iterator(*table->m_model.get(), ON_ModelComponent::Type::ModelGeometry) {
    m_current = m_iterator.FirstComponentReference();
}

std::shared_ptr<ON_Geometry> ObjectTable::Iterator::operator*() const {
    if (!m_current.IsEmpty()) {
        const ON_ModelGeometryComponent* geom = ON_ModelGeometryComponent::Cast(m_current.ModelComponent());
        if (geom && geom->Geometry(nullptr)) {
            return std::shared_ptr<ON_Geometry>(geom->Geometry(nullptr)->Duplicate());
        }
    }
    return nullptr;
}

ObjectTable::Iterator& ObjectTable::Iterator::operator++() {
    m_current = m_iterator.NextComponentReference();
    return *this;
}

bool ObjectTable::Iterator::IsOver() const {
    return m_current.IsEmpty();
}

ObjectTable::Iterator ObjectTable::Begin() {
    return Iterator(this);
}
