/*
    src/_bindings/casters/uuid_caster.h: Direct conversion ON_UUID <-> Python uuid.UUID

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include "../bindings.h"

namespace nb = nanobind;

namespace nanobind::detail {

template <>
struct type_caster<ON_UUID> {
public:
    NB_TYPE_CASTER(ON_UUID, const_name("uuid.UUID"))

    bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept {
        if (!src || !nb::hasattr(src, "hex"))
            return false;

        std::string hex = nb::cast<std::string>(src.attr("hex"));
        value = ON_UuidFromString(hex.c_str());
        return true;
    }

    static handle from_cpp(const ON_UUID& uuid, rv_policy, cleanup_list*) noexcept {
        char s[37] = {0};
        ON_UuidToString(uuid, s);
        static nb::object uuid_ctor = nb::module_::import_("uuid").attr("UUID");
        return uuid_ctor(s).release();
    }
};

} // namespace nanobind::detail
