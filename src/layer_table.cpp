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

LayerView *LayerTable::FindName(std::wstring name, ON_UUID parentId) {
    ON_ModelComponentReference compref = m_model->LayerFromName(parentId, name.c_str());
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);
    return nullptr;
}

const LayerView *LayerTable::Get(std::wstring full_name) {
    const int num_layers = LayerTable::Count();
    for (int i = 0; i <= num_layers; ++i) {
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

LayerView *LayerTable::IterIndex(int index) {
    return FindIndex(index);
}

LayerView *LayerTable::FindIndex(int index) {
    ON_ModelComponentReference compref = m_model->LayerFromIndex(index);
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);

    return nullptr;
}

LayerView *LayerTable::FindId(ON_UUID id) {
    ON_ModelComponentReference compref = m_model->LayerFromId(id);
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);
    return nullptr;
}

// --------------------- Iterator helpers ------- //
//template <typename IT>
//struct PyBNDIterator {
//    PyBNDIterator(const IT table, py::object ref)
//        : seq(table), ref(ref) {}
//
//    py::object next() {
//        if (index >= seq.Count())
//            throw py::stop_iteration();
//        LayerView* lv = const_cast<IT>(seq).IterIndex(index++);
//        //std::cout << typeid(*lv).name() << std::endl;
//        //static_assert(std::is_same_v<decltype(lv), LayerView*>, "Type mismatch!");
//        return py::cast(lv, py::rv_policy::reference);  // or take_ownership if appropriate
//        //return py::cast(reinterpret_cast<LayerView*>(lv), py::rv_policy::reference);
//    }
//
//    const IT seq;
//    py::object ref;
//    int index = 0;
//};
