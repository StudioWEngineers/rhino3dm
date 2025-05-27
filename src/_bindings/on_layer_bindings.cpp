//#include "../layer.h"
#include "color_caster.h"
#include "on_layer_bindings.h"
#include "uuid_caster.h"


void ONLayerBindings(nb::module_& m) {
    nb::class_<ON_Layer>(m, "ONLayer")
        .def(nb::init<>())
        //.def("__repr__", &ON_Layer::ToString)

        .def("unset_persistent_locking", &ON_Layer::UnsetPersistentLocking)
        .def("unset_persistent_visibility", &ON_Layer::UnsetPersistentVisibility)

        //.def_prop_ro("full_path", &ON_Layer::GetFullPath)
        //.def_prop_rw("index", &ON_ModelComponent::Index, &ON_Layer::SetIndex)
        .def_prop_rw(
            "index",
            [](const ON_Layer& self) { return self.Index(); },
            [](ON_Layer& self, int i) { self.SetIndex(i); }
        )
        //.def_prop_ro_static("path_separator", &ON_Layer::GetPathSeparator)
        .def_prop_ro_static(
            "path_separator",
            [](nb::handle /*cls*/) -> std::string {
                ON_String utf8_str(ON_ModelComponent::NamePathSeparator);
                const char* utf8 = utf8_str.Array();
                return utf8 ? std::string(utf8) : std::string();
            }
        )
        .def_prop_rw("color", &ON_Layer::Color, &ON_Layer::SetColor)
        .def_prop_rw("iges_level", &ON_Layer::IgesLevel, &ON_Layer::SetIgesLevel)
        //.def_prop_rw("is_expanded", &ON_Layer::m_bExpanded, &ON_Layer::SetIsExpanded)
        .def_prop_rw("is_expanded",
            [](const ON_Layer& self) { return self.m_bExpanded; },
            [](ON_Layer& self, bool is_expanded) { self.m_bExpanded = is_expanded; }
        )
        .def_prop_rw("is_locked", &ON_Layer::IsLocked, &ON_Layer::SetLocked)
        //.def_prop_rw("is_visible", &ON_Layer::IsVisible, &ON_Layer::SetVisible)
        .def_prop_rw(
            "is_visible",
            [](const ON_Layer& self) { return self.IsVisible(); },
            [](ON_Layer& self, bool is_visible) { self.SetVisible(is_visible); }
        )
        //.def_prop_rw("layer_uuid", &ON_Layer::Id, &ON_Layer::SetId)
        .def_prop_rw(
            "layer_uuid",
            [](const ON_Layer& self) { return self.Id(); },
            [](ON_Layer& self, ON_UUID on_uuid) { self.SetId(on_uuid); }
        )
        .def_prop_rw("line_type_index", &ON_Layer::LinetypeIndex, &ON_Layer::SetLinetypeIndex)
        //.def_prop_rw("name", &ON_Layer::GetName, &ON_Layer::SetName)
        .def_prop_rw(
            "name",
            [](const ON_Layer &self) -> std::string {
                ON_String utf8_str(self.Name());
                const char* utf8 = utf8_str.Array();
                return utf8 ? std::string(utf8) : std::string();
            },
            [](ON_Layer &self, const std::string& value) {
                ON_wString wname(value.c_str());
                self.SetName(wname);
            }
        )
        .def_prop_rw("parent_uuid", &ON_Layer::ParentLayerId, &ON_Layer::SetParentLayerId)
        .def_prop_rw("persistent_locking", &ON_Layer::PersistentLocking, &ON_Layer::SetPersistentLocking)
        .def_prop_rw("persistent_visibility", &ON_Layer::PersistentVisibility, &ON_Layer::SetPersistentVisibility)
        .def_prop_rw("plot_color", &ON_Layer::PlotColor, &ON_Layer::SetPlotColor)
        .def_prop_rw("plot_weight", &ON_Layer::PlotWeight, &ON_Layer::SetPlotWeight)
        .def_prop_rw("render_material_index", &ON_Layer::RenderMaterialIndex, &ON_Layer::SetRenderMaterialIndex)

        .def_prop_ro("parent_uuid_is_null", &ON_Layer::ParentIdIsNil)
        .def_prop_ro("parent_uuid_is_not_null", &ON_Layer::ParentIdIsNotNil)
    ;
}
