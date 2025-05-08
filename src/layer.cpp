#include "layer.h"

#include <sstream>
#include <locale>
#include <codecvt>


Layer::Layer() {
    m_layer = new ON_Layer();

    ON_ModelComponent* model_component = ON_ModelComponent::Cast(m_layer);
    if (model_component == nullptr) {
        model_component = ON_ModelGeometryComponent::CreateManaged(m_layer, nullptr, nullptr);
    }
    if (model_component) {
        m_comp_ref = ON_ModelComponentReference::CreateForExperts(model_component, true);
    }
}

Layer::~Layer() {
    if (m_layer != nullptr && m_comp_ref.IsEmpty()) {
        delete m_layer;
        m_layer = nullptr;
    }
}

const ON_Layer* Layer::LayerHandle() const {
    return m_layer;
}

std::wstring Layer::PathSeparator() {
    return std::wstring(ON_ModelComponent::NamePathSeparator.Array());
}

std::wstring Layer::GetName() const {
    return std::wstring(m_layer->NameAsPointer());
}

void Layer::SetName(const std::wstring& name) {
    m_layer->SetName(name.c_str());
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

int Layer::GetIgesLevel() const {
    return m_layer->IgesLevel();
}

void Layer::SetIgesLevel(int level) {
    m_layer->SetIgesLevel(level);
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

void Layer::SetPersistentVisibility(bool persistent_visibility) {
    if (persistent_visibility) {
        m_layer->SetPersistentVisibility(persistent_visibility);
    } else {
        m_layer->UnsetPersistentVisibility();
    }
}

bool Layer::GetPersistentLocking() const {
    return m_layer->PersistentLocking();
}

void Layer::SetPersistentLocking(bool persistent_locking) {
    if (persistent_locking) {
        m_layer->SetPersistentLocking(persistent_locking);
    } else {
        m_layer->UnsetPersistentLocking();
    }
}

bool Layer::IsExpanded() const {
    return m_layer->m_bExpanded;
}

void Layer::SetExpanded(bool is_expanded) {
    m_layer->m_bExpanded = is_expanded;
}

const std::string Layer::ToString() const {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::string name_str = convert.to_bytes(this->GetName());

    ON_Color color = this->GetColor();
    std::ostringstream color_stream;
    color_stream << "(" << color.Red() << ", " << color.Green() << ", " << color.Blue() << ", " << 255 - color.Alpha() << ")";

    ON_Color p_color = this->GetPlotColor();
    std::ostringstream p_color_stream;
    p_color_stream << "(" << p_color.Red() << ", " << p_color.Green() << ", " << p_color.Blue() << ", " << 255 - p_color.Alpha() << ")";

    std::ostringstream output;
    output << "Layer with properties:\n"
           << "\tcolor = " << color_stream.str() << "\n"
           << "\tiges_level = " << this->GetIgesLevel() << "\n"
           << "\tis_expanded = " << this->IsExpanded() << "\n"
           << "\tis_visible = " << std::boolalpha << this->IsVisible() << "\n"
           << "\tline_type_index = " << this->GetLinetypeIndex() << "\n"
           << "\tname = '" << name_str << "',\n"
           << "\tpersistent_locking = " << this->GetPersistentLocking() << "\n"
           << "\tpersistent_visibility = " << this->GetPersistentVisibility() << "\n"
           << "\tplot_color = " << p_color_stream.str() << "\n"
           << "\tplot_weight = " << this->GetPlotWeight() << "\n"
           << "\trender_material_index = " << this->GetRenderMaterialIndex() << "\n"
           ;
    return output.str();
}
