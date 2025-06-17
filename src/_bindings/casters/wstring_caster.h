/*
    src/_bindings/casters/wstring_caster.h: Direct conversion ON_wString <-> Python str

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include "../bindings.h"

namespace nb = nanobind;

namespace nanobind::detail {

template <>
struct type_caster<ON_wString> {
public:
    NB_TYPE_CASTER(ON_wString, const_name("ON_wString"))

    // Python str -> ON_wString
    bool from_python(nb::handle src, uint8_t flags, cleanup_list* cleanup) noexcept {
        if (!nb::isinstance<nb::str>(src))
            return false;

        try {
            std::string temp = nb::str(src).c_str();
            value = ON_wString(temp.c_str());
            return true;

        } catch (...) {
            return false;
        }
    }

    // ON_wString -> Python str
    static nb::handle from_cpp(const ON_wString& src, rv_policy policy, cleanup_list* cleanup) noexcept {
        ON_String utf8_str = ON_String(src);
        return nb::str(utf8_str.Array()).release();
    }
};

} // namespace nanobind::detail
