#include "layer_view.h"

#include <sstream>
#include <locale>
#include <codecvt>


LayerView::LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref) {
    SetTrackedPointer(layer, compref);
}

LayerView::LayerView(ON_Layer* layer, const ON_ModelComponentReference* compref, std::shared_ptr<ONX_Model>& model) {
    SetTrackedPointer(layer, compref);
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

std::wstring LayerView::PathSeparator() {
    return std::wstring(ON_ModelComponent::NamePathSeparator.Array());
}

ON_UUID LayerView::GetId() const {
    return m_layer->Id();
}

std::wstring LayerView::GetName() const {
    return std::wstring(m_layer->NameAsPointer());
}

std::wstring LayerView::GetFullPath() const {
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

ON_UUID LayerView::GetParentLayerId() const {
    return m_layer->ParentId();
}

int LayerView::GetIgesLevel() const {
    return m_layer->IgesLevel();
}

ON_Color LayerView::GetColor() const {
    return m_layer->Color();
}

ON_Color LayerView::GetPlotColor() const {
    return m_layer->PlotColor();
}

double LayerView::GetPlotWeight() const {
    return m_layer->PlotWeight();
}

int LayerView::GetLinetypeIndex() const {
    return m_layer->LinetypeIndex();
}

int LayerView::GetRenderMaterialIndex() const {
    return m_layer->RenderMaterialIndex();
}

bool LayerView::IsVisible() const {
    return m_layer->IsVisible();
}

bool LayerView::IsLocked() const {
    return m_layer->IsLocked();
}

bool LayerView::GetPersistentVisibility() const {
    return m_layer->PersistentVisibility();
}

bool LayerView::GetPersistentLocking() const {
    return m_layer->PersistentLocking();
}

bool LayerView::IsExpanded() const {
    return m_layer->m_bExpanded;
}

const std::string LayerView::ToString() const {
    // Convert std::wstring to std::string for name
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::string name_str = convert.to_bytes(this->GetName());

    // Convert ON_Color to string
    ON_Color color = this->GetPlotColor();
    std::ostringstream color_stream;
    color_stream << "(" << color.Red() << ", " << color.Green() << ", " << color.Blue() << ")";
    std::string color_str = color_stream.str();

    // Return the final string representation
    return "<Layer(name='" + name_str + "', plot_color=" + color_str + ")>";
}

void LayerView::SetTrackedPointer(ON_Layer* layer, const ON_ModelComponentReference* compref) {
    m_layer = layer;

    if (compref) {
        m_comp_ref = *compref;
    } else {
        ON_ModelComponent* model_component = ON_ModelComponent::Cast(layer);
        if (model_component == nullptr) {
            model_component = ON_ModelGeometryComponent::CreateManaged(layer, nullptr, nullptr);
        }
        if (model_component) {
            m_comp_ref = ON_ModelComponentReference::CreateForExperts(model_component, true);
        }
    }
}
