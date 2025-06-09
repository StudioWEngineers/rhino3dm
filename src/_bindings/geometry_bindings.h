/*
    src/_bindings/geometry_bindings.h: Exposing Geometry to Python

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include "bindings.h"

namespace nb = nanobind;

void GeometryBindings(nb::module_& m);
