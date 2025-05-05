#include "layer.h"


Layer::Layer() {
    SetTrackedPointer(new ON_Layer(), nullptr);
}

Layer::~Layer() {
    if (m_layer != nullptr && m_component_ref.IsEmpty()) {
        delete m_layer;
        m_layer = nullptr;
    }
}

void Layer::SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref) {
    m_layer = layer;

    if (compref) {
        m_component_ref = *compref;
    } else {
        ON_ModelComponent* model_component = ON_ModelComponent::Cast(layer);
        if (model_component == nullptr) {
            model_component = ON_ModelGeometryComponent::CreateManaged(layer, nullptr, nullptr);
        }
        if (model_component) {
            m_component_ref = ON_ModelComponentReference::CreateForExperts(model_component, true);
        }
    }
}

std::wstring Layer::GetName() const {
    return std::wstring(m_layer->NameAsPointer());
}

void Layer::SetName(const std::wstring& name) {
    m_layer->SetName(name.c_str());
}

ON_Color Layer::GetColor() const {
    return m_layer->Color();
}

void Layer::SetColor(const ON_Color& on_color) {
    m_layer->SetColor(on_color);
}

ON_Color Layer::GetPlotColor() const {
    return m_layer->PlotColor();
}

void Layer::SetPlotColor(const ON_Color& on_color) {
    m_layer->SetPlotColor(on_color);
}

double Layer::GetPlotWeight() const {
    return m_layer->PlotWeight();
}

void Layer::SetPlotWeight(double weight) {
    m_layer->SetPlotWeight(weight);
}

int Layer::GetLinetypeIndex() const {
    return m_layer->LinetypeIndex();
}

void Layer::SetLinetypeIndex(int index) {
    m_layer->SetLinetypeIndex(index);
}

int Layer::GetRenderMaterialIndex() const {
    return m_layer->RenderMaterialIndex();
}

void Layer::SetRenderMaterialIndex(int index) {
    m_layer->SetRenderMaterialIndex(index);
}

bool Layer::IsVisible() const {
    return m_layer->IsVisible();
}

void Layer::SetVisible(bool visible) {
    m_layer->SetVisible(visible);
}

bool Layer::IsLocked() const {
    return m_layer->IsLocked();
}

void Layer::SetLocked(bool locked) {
    m_layer->SetLocked(locked);
}

bool Layer::GetPersistentVisibility() const {
    return m_layer->PersistentVisibility();
}

void Layer::SetPersistentVisibility(bool persistent) {
    m_layer->SetPersistentVisibility(persistent);
}

void Layer::UnsetPersistentVisibility() {
    m_layer->UnsetPersistentVisibility();
}

bool Layer::GetPersistentLocking() const {
    return m_layer->PersistentLocking();
}

void Layer::SetPersistentLocking(bool persistent) {
    m_layer->SetPersistentLocking(persistent);
}

void Layer::UnsetPersistentLocking() {
    m_layer->UnsetPersistentLocking();
}

int Layer::GetIgesLevel() const {
    return m_layer->IgesLevel();
}

void Layer::SetIgesLevel(int level) {
    m_layer->SetIgesLevel(level);
}

std::wstring Layer::GetFullPath() const {
    ONX_Model* model = m_model.get();
    if (nullptr == model) {
        return GetName();
    }

    ON_wString fullPath = m_layer->Name();
    ON_UUID parent_id = m_layer->ParentId();
    while (ON_UuidIsNotNil(parent_id)) {
        ON_ModelComponentReference compref = model->LayerFromId(parent_id);
        const ON_ModelComponent* model_component = compref.ModelComponent();
        ON_Layer* modellayer = const_cast<ON_Layer*>(ON_Layer::Cast(model_component));
        if (nullptr == modellayer) {
            break;
        }

        ON_wString parentName = modellayer->Name();
        fullPath = parentName + ON_ModelComponent::NamePathSeparator + fullPath;
        parent_id = modellayer->ParentId();
    }

    return std::wstring(fullPath.Array());
}

ON_UUID Layer::GetParentLayerId() const {
    return m_layer->ParentId();
}

void Layer::SetParentLayerId(ON_UUID on_uuid) {
    m_layer->SetParentLayerId(on_uuid);
}
