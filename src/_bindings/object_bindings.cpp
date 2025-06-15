#include "object_bindings.h"


void ObjectBindings(nb::module_& m) {

    nb::class_<ON_Object>(m, "OpenNURBSObject")

        .def(nb::init<>())

        .def("is_corrupt", &ON_Object::IsCorrupt)

        .def("is_valid", &ON_Object::IsValid)

        .def("get_user_string", &ON_Object::GetUserString)

        .def("get_user_string_keys", &ON_Object::GetUserStringKeys)

        .def("get_user_strings", &ON_Object::GetUserStrings)

        .def("set_user_string", &ON_Object::SetUserString)

        .def("set_user_strings", &ON_Object::SetUserStrings)

        .def("user_string_count", &ON_Object::UserStringCount)
    ;
}
