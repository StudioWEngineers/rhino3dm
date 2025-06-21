/*
    src/utilities/utilities.h: Helper functions to be used across the project.

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include <string>


namespace Utilities {

    std::wstring utf8_to_wchar(const std::string& str);

    std::string wchar_to_utf8(const wchar_t* wstr);

}
