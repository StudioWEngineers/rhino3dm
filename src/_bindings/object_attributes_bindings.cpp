#include "object_attributes_bindings.h"


void ObjectAttributesBindings(nb::module_& m) {

    nb::class_<ON_3dmObjectAttributes, ON_Object>(m, "ObjectAttributes")

        /*magic methods*/
        .def(nb::init<>())

        /*other methods*/

    ;
}
