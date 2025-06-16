#pragma once

#include "bindings.h"
//#include "../lib/opennurbs/opennurbs_uuid.h"
#include "opennurbs_uuid.h"


namespace nb = nanobind;

namespace nanobind::detail {

template <>
struct type_caster<ON_UUID> {
public:
    NB_TYPE_CASTER(ON_UUID, const_name("uuid.UUID"))

    // Python → C++
    bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept {
        if (!src || !nb::hasattr(src, "hex"))
            return false;

        std::string hex = nb::cast<std::string>(src.attr("hex"));
        value = ON_UuidFromString(hex.c_str());
        return true;
    }

    // C++ → Python
    static handle from_cpp(const ON_UUID& uuid, rv_policy, cleanup_list*) noexcept {
        char s[37] = {0};
        ON_UuidToString(uuid, s);
        static nb::object uuid_ctor = nb::module_::import_("uuid").attr("UUID");
        return uuid_ctor(s).release();
    }
};

} // namespace nanobind::detail
