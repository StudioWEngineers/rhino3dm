/*
    src/utilities/layer_utilities.h: Helper functions for the ON_layer class.

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include <string>

#include "../opennurbs_includes.h"


namespace LayerUtilities {

    std::string GetName(const ON_Layer& layer);

    std::string GetPathSeparator();

    void SetName(ON_Layer& layer, const std::string& name);

    std::string ToString(const ON_Layer& layer);

}
