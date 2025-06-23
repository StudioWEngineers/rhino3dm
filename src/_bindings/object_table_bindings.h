/*
    src/_bindings/object_table_bindings.h: Exposing helper class ObjectTable to Python

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include "bindings.h"

namespace nb = nanobind;

nb::object GeometryObjectWrapper(const std::shared_ptr<ON_Object>& geom);

void ObjectTableBindings(nb::module_& m);
