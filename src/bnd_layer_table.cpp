#include "bindings.h"
// #include "bnd_layer_table.h"
//  uncomment the previous line leads to class redifintion
// https://stackoverflow.com/questions/25713718/error-c2011-class-type-redefinition
//#include "base64.h"

BND_File3dmLayerTable::BND_File3dmLayerTable(std::shared_ptr<ONX_Model> m) {
    m_model = m;
}

int BND_File3dmLayerTable::Add(const Layer &layer) {
    const ON_Layer *l = layer.m_layer;
    ON_ModelComponentReference mr = m_model->AddModelComponent(*l);
    const ON_Layer *managed_layer = ON_Layer::FromModelComponentRef(mr, nullptr);
    int layer_index = (nullptr != managed_layer) ? managed_layer->Index() : ON_UNSET_INT_INDEX;
    return layer_index;
}

int BND_File3dmLayerTable::Count() const {
    return m_model.get()->ActiveComponentCount(ON_ModelComponent::Type::Layer);
}

bool BND_File3dmLayerTable::Delete(BND_UUID id) {
    // ON_UUID _id = Binding_to_ON_UUID(id);
    ON_ModelComponentReference cr = m_model->RemoveModelComponent(ON_ModelComponent::Type::Layer, Binding_to_ON_UUID(id));
    return !cr.IsEmpty();
    // return DeleteModelComponent(id, ON_ModelComponent::Type::Layer, m_model);
}

LayerView *BND_File3dmLayerTable::FindName(std::wstring name, BND_UUID parentId) {
    ON_UUID id = Binding_to_ON_UUID(parentId);
    ON_ModelComponentReference compref = m_model->LayerFromName(id, name.c_str());
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);
    return nullptr;
}

const LayerView *BND_File3dmLayerTable::Get(std::wstring full_name) {
    const int num_layers = BND_File3dmLayerTable::Count();
    for (int i = 0; i <= num_layers; ++i) {
        const std::wstring name = BND_File3dmLayerTable::FindIndex(i)->GetFullPath();
        if (full_name == name) {
            ON_ModelComponentReference cr = m_model->ComponentFromIndex(ON_ModelComponent::Type::Layer, i);
            ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(cr.ModelComponent()));
            return new LayerView(modellayer, &cr, m_model);
        }
    }
    throw py::index_error();
}

bool BND_File3dmLayerTable::Has(std::wstring full_name) {
    const int num_layers = BND_File3dmLayerTable::Count();
    for (int i = 0; i <= num_layers; ++i) {
        const std::wstring name = BND_File3dmLayerTable::FindIndex(i)->GetFullPath();
        if (full_name == name) {
            return true;
        }
    }
    return false;
}

LayerView *BND_File3dmLayerTable::IterIndex(int index) {
    return FindIndex(index);
}

LayerView *BND_File3dmLayerTable::FindIndex(int index) {
    ON_ModelComponentReference compref = m_model->LayerFromIndex(index);
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);

    throw py::index_error();
}

LayerView *BND_File3dmLayerTable::FindId(BND_UUID id) {
    ON_UUID _id = Binding_to_ON_UUID(id);
    ON_ModelComponentReference compref = m_model->LayerFromId(_id);
    const ON_ModelComponent *model_component = compref.ModelComponent();
    ON_Layer *modellayer = const_cast<ON_Layer *>(ON_Layer::Cast(model_component));
    if (modellayer)
        return new LayerView(modellayer, &compref, m_model);
    return nullptr;
}

// --------------------- Iterator helpers ------- //
template <typename IT, typename ET>
struct PyBNDIterator {
    PyBNDIterator(const IT table, py::object ref)
        : seq(table), ref(ref) {}

    ET next() {
        if (index >= seq.Count())
            throw py::stop_iteration();
        return const_cast<IT>(seq).IterIndex(index++);
    }

    const IT seq;
    py::object ref;
    int index = 0;
};

void initLayerTableBindings(rh3dmpymodule &m) {
    py::class_<PyBNDIterator<BND_File3dmLayerTable &, LayerView *>>(m, "__LayerIterator")
        .def("__iter__", [](PyBNDIterator<BND_File3dmLayerTable &, LayerView *> &it) -> PyBNDIterator<BND_File3dmLayerTable &, LayerView *> & { return it; })
        .def("__next__", &PyBNDIterator<BND_File3dmLayerTable &, LayerView *>::next);

    py::class_<BND_File3dmLayerTable>(m, "LayerTable")
        .def("__len__", &BND_File3dmLayerTable::Count)
        .def("__getitem__", &BND_File3dmLayerTable::FindIndex)
#if !defined(NANOBIND)
        .def("__iter__", [](py::object s) { return PyBNDIterator<BND_File3dmLayerTable &, LayerView *>(s.cast<BND_File3dmLayerTable &>(), s); })
#endif
        .def("Add", &BND_File3dmLayerTable::Add, py::arg("layer"))
        .def("Delete", &BND_File3dmLayerTable::Delete, py::arg("id"))
        .def("FindName", &BND_File3dmLayerTable::FindName, py::arg("name"), py::arg("parentId"))
        .def("FindIndex", &BND_File3dmLayerTable::FindIndex, py::arg("index"))
        .def("FindId", &BND_File3dmLayerTable::FindId, py::arg("id"))
        .def("has", &BND_File3dmLayerTable::Has, "Return True if the layer is found, False otherwise.", py::arg("full_name"))
        .def("get", &BND_File3dmLayerTable::Get, "Return the immutable layer if it is found, raise IndexError otherwise.", py::arg("full_name"));
}
