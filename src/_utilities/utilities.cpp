#include <codecvt>
#include <locale>
#include <sstream>

#include "utilities.h"


namespace Utilities {

std::wstring utf8_to_wchar(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string wchar_to_utf8(const wchar_t* wstr) {
    if (!wstr) return {};

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

} // namespace Utilities
