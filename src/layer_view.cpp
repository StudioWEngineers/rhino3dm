#include "layer_view.h"

#include <sstream>
#include <locale>
#include <codecvt>


LayerView::LayerView(ON_Layer* layer, const ON_ModelComponentReference* comp_ref) {
    SetTrackedPointer(layer, comp_ref);
}

LayerView::LayerView(ON_Layer* layer, const ON_ModelComponentReference* comp_ref, std::shared_ptr<ONX_Model>& model) {
    SetTrackedPointer(layer, comp_ref);
    m_model = model;
}

LayerView::~LayerView() {
    if (m_layer != nullptr && m_comp_ref.IsEmpty()) {
        delete m_layer;
        m_layer = nullptr;
    }
}

const ON_Layer* LayerView::LayerHandle() const {
    return m_layer;
}

ON_Color LayerView::GetColor() const {
    return m_layer->Color();
}

std::wstring LayerView::GetFullPath() const {
    ONX_Model* model = m_model.get();
    if (model == nullptr) {
        return GetName();
    }

    ON_wString full_name = m_layer->Name();
    ON_UUID parent_id = m_layer->ParentId();
    while (ON_UuidIsNotNil(parent_id)) {
        ON_ModelComponentReference comp_ref = model->LayerFromId(parent_id);
        ON_Layer* layer = const_cast<ON_Layer*>(ON_Layer::Cast(comp_ref.ModelComponent()));
        if (layer == nullptr) {
            break;
        }

        ON_wString parent_name = layer->Name();
        full_name = parent_name + ON_ModelComponent::NamePathSeparator + full_name;
        parent_id = layer->ParentId();
    }

    return std::wstring(full_name.Array());
}

int LayerView::GetIgesLevel() const {
    return m_layer->IgesLevel();
}

int LayerView::GetIndex() const {
    return m_layer->Index();
}

bool LayerView::GetIsExpanded() const {
    return m_layer->m_bExpanded;
}

bool LayerView::GetIsLocked() const {
    return m_layer->IsLocked();
}

bool LayerView::GetIsVisible() const {
    return m_layer->IsVisible();
}

ON_UUID LayerView::GetLayerId() const {
    return m_layer->Id();
}

int LayerView::GetLinetypeIndex() const {
    return m_layer->LinetypeIndex();
}

std::wstring LayerView::GetName() const {
    return std::wstring(m_layer->NameAsPointer());
}

ON_UUID LayerView::GetParentLayerId() const {
    return m_layer->ParentId();
}

std::wstring LayerView::GetPathSeparator() {
    return std::wstring(ON_ModelComponent::NamePathSeparator.Array());
}

bool LayerView::GetPersistentLocking() const {
    return m_layer->PersistentLocking();
}

bool LayerView::GetPersistentVisibility() const {
    return m_layer->PersistentVisibility();
}

ON_Color LayerView::GetPlotColor() const {
    return m_layer->PlotColor();
}

double LayerView::GetPlotWeight() const {
    return m_layer->PlotWeight();
}

int LayerView::GetRenderMaterialIndex() const {
    return m_layer->RenderMaterialIndex();
}

const std::string LayerView::ToString() const {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::string name_str = convert.to_bytes(this->GetName());
    std::string full_name_str = convert.to_bytes(this->GetFullPath());
    std::string path_separator_str = convert.to_bytes(this->GetPathSeparator());

    char p_uuid_str[37];
    char uuid_str[37];
    ON_UuidToString(this->GetParentLayerId(), p_uuid_str);
    ON_UuidToString(this->GetLayerId(), uuid_str);

    ON_Color color = this->GetColor();
    std::ostringstream color_stream;
    color_stream << "(" << color.Red() << ", " << color.Green() << ", " << color.Blue() << ", " << 255 - color.Alpha() << ")";

    ON_Color p_color = this->GetPlotColor();
    std::ostringstream p_color_stream;
    p_color_stream << "(" << p_color.Red() << ", " << p_color.Green() << ", " << p_color.Blue() << ", " << 255 - p_color.Alpha() << ")";

    std::ostringstream output;
    output << "LayerView with properties:\n"
           << "\tcolor = " << color_stream.str() << "\n"
           << "\tfull_path = '" << full_name_str << "'\n"
           << "\tiges_level = " << this->GetIgesLevel() << "\n"
           << "\tindex = " << this->GetIndex() << "\n"
           << "\tis_expanded = " << std::boolalpha << this->GetIsExpanded() << "\n"
           << "\tis_locked = " << this->GetIsLocked() << "\n"
           << "\tis_visible = " << this->GetIsVisible() << "\n"
           << "\tlayer_uuid = " << std::string(uuid_str) << "\n"
           << "\tline_type_index = " << this->GetLinetypeIndex() << "\n"
           << "\tname = '" << name_str << "'\n"
           << "\tparent_uuid = " << std::string(p_uuid_str) << "\n"
           << "\tpath separator = " << path_separator_str << "\n"
           << "\tpersistent_locking = " << this->GetPersistentLocking() << "\n"
           << "\tpersistent_visibility = " << this->GetPersistentVisibility() << "\n"
           << "\tplot_color = " << p_color_stream.str() << "\n"
           << "\tplot_weight = " << this->GetPlotWeight() << "\n"
           << "\trender_material_index = " << this->GetRenderMaterialIndex() << "\n";
    return output.str();
}


void LayerView::SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* comp_ref) {
    m_layer = layer;

    if (comp_ref) {
        m_comp_ref = *comp_ref;
    } else {
        ON_ModelComponent* mod_comp = ON_ModelComponent::Cast(layer);
        if (mod_comp == nullptr) {
            mod_comp = ON_ModelGeometryComponent::CreateManaged(layer, nullptr, nullptr);
        }
        if (mod_comp) {
            m_comp_ref = ON_ModelComponentReference::CreateForExperts(mod_comp, true);
        }
    }
}
