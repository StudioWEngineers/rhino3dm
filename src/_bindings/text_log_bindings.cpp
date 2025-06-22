#include "casters/on_wstring_caster.h"
#include "text_log_bindings.h"


void TextLogBindings(nb::module_& m) {

    auto on_textlog = nb::class_<ON_TextLog>(m, "TextLog")

        /*magic methods*/
        .def(nb::init<>())

        /*static methods*/
        .def_static("null", []() -> ON_TextLog* { return &ON_TextLog::Null; }, nb::rv_policy::reference)

        /*other methods*/
        .def("decrease_level_of_detail", &ON_TextLog::DecreaseLevelOfDetail)

        .def("get_level_of_detail", &ON_TextLog::GetLevelOfDetail)

        .def("increase_level_of_detail", &ON_TextLog::IncreaseLevelOfDetail)

        .def("is_null", &ON_TextLog::IsNull)

        .def("level_of_detail_is_at_least", &ON_TextLog::LevelOfDetailIsAtLeast)

        .def("set_level_of_detail", &ON_TextLog::SetLevelOfDetail)
    ;

    nb::enum_<ON_TextLog::LevelOfDetail>(on_textlog, "LevelOfDetail")

        .value("Minimum", ON_TextLog::LevelOfDetail::Minimum)

        .value("Medium", ON_TextLog::LevelOfDetail::Medium)

        .value("Maximum", ON_TextLog::LevelOfDetail::Maximum)

        .export_values()
    ;
}
