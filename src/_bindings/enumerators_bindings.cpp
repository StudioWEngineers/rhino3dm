#include "enumerators_bindings.h"


void EnumeratorsBindings(nb::module_& m) {

    nb::enum_<ON::object_color_source>(m, "ObjectColorSource")
        .value("from_layer", ON::object_color_source::color_from_layer)
        .value("from_object", ON::object_color_source::color_from_object)
        .value("from_material", ON::object_color_source::color_from_material)
        .value("from_parent", ON::object_color_source::color_from_parent)
        .export_values()
    ;

    nb::enum_<ON::object_mode>(m, "ObjectMode")
        .value("normal", ON::object_mode::normal_object)
        .value("hidden", ON::object_mode::hidden_object)
        .value("locked", ON::object_mode::locked_object)
        .value("idef", ON::object_mode::idef_object)
        .value("mode_count", ON::object_mode::object_mode_count)
        .export_values()
    ;

    nb::enum_<ON::plot_color_source>(m, "PlotColorSource")
        .value("from_object", ON::plot_color_source::plot_color_from_layer)
        .value("from_material", ON::plot_color_source::plot_color_from_object)
        .value("from_layer", ON::plot_color_source::plot_color_from_display)
        .value("from_parent", ON::plot_color_source::plot_color_from_parent)
        .export_values()
    ;
}
