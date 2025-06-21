#include "../utilities/object_utilities.h"
#include "object_bindings.h"


void ObjectBindings(nb::module_& m) {

    nb::class_<ON_Object>(m, "OpenNURBSObject")

        /*magic methods*/
        .def(nb::init<>())

        /*other methods*/
        .def("get_user_string",
            [] (const ON_Object& self, std::string key) {
                return ObjectUtilities::GetUserString(self, key);
            }
        )

        .def("is_corrupt", &ON_Object::IsCorrupt)

        .def("is_valid", &ON_Object::IsValid, nb::arg("text_log") = nullptr)

        .def("remove_user_string",
            [] (ON_Object& self, std::string key) {
                return ObjectUtilities::RemoveUserString(self, key);
            }
        )

        .def("set_user_string",
            [] (ON_Object& self, std::string key, std::string value) {
                return ObjectUtilities::SetUserString(self, key, value);
            }
        )

        .def("user_string_count", &ON_Object::UserStringCount)
    ;
}
