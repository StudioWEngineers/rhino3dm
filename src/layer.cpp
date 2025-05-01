#include "layer.h"

Layer::Layer() {
    SetTrackedPointer(new ON_Layer(), nullptr);
}

Layer::Layer(ON_Layer* layer, const ON_ModelComponentReference* compref) {
    SetTrackedPointer(layer, compref);
}

Layer::Layer(ON_Layer* layer, const ON_ModelComponentReference* compref, std::shared_ptr<ONX_Model>& model) {
    SetTrackedPointer(layer, compref);
    m_model = model;
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

std::wstring Layer::PathSeparator() {
    return std::wstring(ON_ModelComponent::NamePathSeparator.Array());
}

std::wstring Layer::GetFullPath() const {
    if (!m_model) {
        return GetName();
    }

    ONX_Model* model = m_model.get();
    ON_wString fullPath = m_layer->Name();
    ON_UUID parent_id = m_layer->ParentId();

    while (ON_UuidIsNotNil(parent_id)) {
        ON_ModelComponentReference compref = model->LayerFromId(parent_id);
        const ON_ModelComponent* model_component = compref.ModelComponent();
        ON_Layer* parent_layer = const_cast<ON_Layer*>(ON_Layer::Cast(model_component));
        if (!parent_layer) {
            break;
        }

        ON_wString parentName = parent_layer->Name();
        fullPath = parentName + ON_ModelComponent::NamePathSeparator + fullPath;
        parent_id = parent_layer->ParentId();
    }

    return std::wstring(fullPath.Array());
}

std::wstring Layer::GetName() const {
    return std::wstring(m_layer->NameAsPointer());
}

void Layer::SetName(const std::wstring& name) {
    m_layer->SetName(name.c_str());
}

bool Layer::HasPerViewportSettings(BND_UUID viewportId) const {
    ON_UUID id = Binding_to_ON_UUID(viewportId);
    return m_layer->HasPerViewportSettings(id);
}

void Layer::DeletePerViewportSettings(BND_UUID viewportId) {
    ON_UUID id = Binding_to_ON_UUID(viewportId);
    m_layer->DeletePerViewportSettings(id);
}

BND_Color Layer::GetColor() const {
    return ON_Color_to_Binding(m_layer->Color());
}

void Layer::SetColor(const BND_Color& color) {
    m_layer->SetColor(Binding_to_ON_Color(color));
}

BND_UUID Layer::GetParentLayerId() const {
    return ON_UUID_to_Binding(m_layer->ParentId());
}

void Layer::SetParentLayerId(BND_UUID id) {
    m_layer->SetParentLayerId(Binding_to_ON_UUID(id));
}

int Layer::GetIgesLevel() const {
    return m_layer->IgesLevel();
}

void Layer::SetIgesLevel(int level) {
    m_layer->SetIgesLevel(level);
}

BND_Color Layer::PerViewportColor(BND_UUID viewportId) const {
    ON_UUID id = Binding_to_ON_UUID(viewportId);
    return ON_Color_to_Binding(m_layer->PerViewportColor(id));
}

void Layer::SetPerViewportColor(BND_UUID viewportId, BND_Color color) {
    ON_UUID id = Binding_to_ON_UUID(viewportId);
    m_layer->SetPerViewportColor(id, Binding_to_ON_Color(color));
}

void Layer::DeletePerViewportColor(BND_UUID viewportId) {
    ON_UUID id = Binding_to_ON_UUID(viewportId);
    m_layer->DeletePerViewportColor(id);
}

BND_Color Layer::GetPlotColor() const {
    return ON_Color_to_Binding(m_layer->PlotColor());
}

bool Layer::IsExpanded() const {
    return m_layer->m_bExpanded;
}

void Layer::SetExpanded(bool e) {
    m_layer->m_bExpanded = e;
}

void Layer::SetPlotColor(const BND_Color& color) {
    m_layer->SetPlotColor(Binding_to_ON_Color(color));
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

void LayerBindings(rh3dmpymodule& m) {
    py::class_<Layer>(m, "Layer")
        .def(py::init<>())
        .def_property_readonly_static("PathSeparator", &Layer::PathSeparator)
        .def_property("Name", &Layer::GetName, &Layer::SetName)
        .def_property_readonly("FullPath", &Layer::GetFullPath)
        .def_property("ParentLayerId", &Layer::GetParentLayerId, &Layer::SetParentLayerId)
        .def_property("IgesLevel", &Layer::GetIgesLevel, &Layer::SetIgesLevel)
        .def("HasPerViewportSettings", &Layer::HasPerViewportSettings, py::arg("viewportId"))
        .def("DeletePerViewportSettings", &Layer::DeletePerViewportSettings, py::arg("viewportId"))
        .def_property("Color", &Layer::GetColor, &Layer::SetColor)
        .def("PerViewportColor", &Layer::PerViewportColor, py::arg("viewportId"))
        .def("SetPerViewportColor", &Layer::SetPerViewportColor, py::arg("viewportId"), py::arg("color"))
        .def("DeletePerViewportColor", &Layer::DeletePerViewportColor, py::arg("viewportId"))
        .def_property("PlotColor", &Layer::GetPlotColor, &Layer::SetPlotColor)
        .def_property("PlotWeight", &Layer::GetPlotWeight, &Layer::SetPlotWeight)
        .def_property("LinetypeIndex", &Layer::GetLinetypeIndex, &Layer::SetLinetypeIndex)
        .def_property("RenderMaterialIndex", &Layer::GetRenderMaterialIndex, &Layer::SetRenderMaterialIndex)
        .def_property("Visible", &Layer::IsVisible, &Layer::SetVisible)
        .def_property("Locked", &Layer::IsLocked, &Layer::SetLocked)
        .def("GetPersistentVisibility", &Layer::GetPersistentVisibility)
        .def("SetPersistentVisibility", &Layer::SetPersistentVisibility, py::arg("persistentVisibility"))
        .def("UnsetPersistentVisibility", &Layer::UnsetPersistentVisibility)
        .def("GetPersistentLocking", &Layer::GetPersistentLocking)
        .def("SetPersistentLocking", &Layer::SetPersistentLocking, py::arg("persistentLocking"))
        .def("UnsetPersistentLocking", &Layer::UnsetPersistentLocking)
        .def_property("Expanded", &Layer::IsExpanded, &Layer::SetExpanded);
}
