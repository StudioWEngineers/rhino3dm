#include "../utilities/layer_utilities.h"
#include "casters/color_caster.h"
#include "casters/uuid_caster.h"
#include "layer_bindings.h"


void LayerBindings(nb::module_& m) {

    nb::class_<ON_Layer>(m, "Layer")

        /*magic methods*/
        .def(nb::init<>())

        .def("__repr__", [](const ON_Layer& self) {return LayerUtilities::ToString(self);})

        /*read-write properties*/
        .def_prop_rw("color", &ON_Layer::Color, &ON_Layer::SetColor)

        .def_prop_rw("iges_level", &ON_Layer::IgesLevel, &ON_Layer::SetIgesLevel)

        .def_prop_rw(
            "is_expanded",
            [](const ON_Layer& self) {
                return self.m_bExpanded;
            },
            [](ON_Layer& self, bool is_expanded) {
                self.m_bExpanded = is_expanded;
            }
        )

        .def_prop_rw("is_locked", &ON_Layer::IsLocked, &ON_Layer::SetLocked)

        .def_prop_rw(
            "is_visible",
            [](const ON_Layer& self) {
                return self.IsVisible();
            },
            [](ON_Layer& self, bool is_visible) {
                self.SetVisible(is_visible);
            }
        )

        .def_prop_rw(
            "layer_uuid",
            [](const ON_Layer& self) {
                return self.Id();
            },
            [](ON_Layer& self, ON_UUID on_uuid) {
                self.SetId(on_uuid);
            }
        )

        .def_prop_rw("line_type_index", &ON_Layer::LinetypeIndex, &ON_Layer::SetLinetypeIndex)

        .def_prop_rw(
            "name",
            [](const ON_Layer& self) -> std::string {
                return LayerUtilities::GetName(self);
            },
            [](ON_Layer& self, const std::string& name) {
                return LayerUtilities::SetName(self, name);
            }
        )

        .def_prop_rw("parent_uuid", &ON_Layer::ParentLayerId, &ON_Layer::SetParentLayerId)

        .def_prop_rw("persistent_locking", &ON_Layer::PersistentLocking, &ON_Layer::SetPersistentLocking)

        .def_prop_rw("persistent_visibility", &ON_Layer::PersistentVisibility, &ON_Layer::SetPersistentVisibility)

        .def_prop_rw("plot_color", &ON_Layer::PlotColor, &ON_Layer::SetPlotColor)

        .def_prop_rw("plot_weight", &ON_Layer::PlotWeight, &ON_Layer::SetPlotWeight)

        .def_prop_rw("render_material_index", &ON_Layer::RenderMaterialIndex, &ON_Layer::SetRenderMaterialIndex)

        .def_prop_rw(
            "index",
            [](const ON_Layer& self) {
                return self.Index();
            },
            [](ON_Layer& self, int index) {
                self.SetIndex(index);
            }
        )

        /*read-only properties*/
        .def_prop_ro("parent_uuid_is_not_null", &ON_Layer::ParentIdIsNotNil)

        .def_prop_ro("parent_uuid_is_null", &ON_Layer::ParentIdIsNil)

        .def_prop_ro(
            "path_separator",
            [](const ON_Layer& /*self*/) -> std::string {
                return LayerUtilities::GetPathSeparator();
            }
        )

        /*other methods*/
        .def("is_valid", &ON_Layer::IsValid, nb::arg("text_log") = nullptr)

        .def("unset_persistent_locking", &ON_Layer::UnsetPersistentLocking)

        .def("unset_persistent_visibility", &ON_Layer::UnsetPersistentVisibility)
    ;
}
