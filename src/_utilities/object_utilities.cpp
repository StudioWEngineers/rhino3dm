#include "object_utilities.h"
#include "utilities.h"


namespace ObjectUtilities {

std::string GetUserString(const ON_Object& on_obj, std::string& key) {
    std::wstring w_key = Utilities::utf8_to_wchar(key);
    ON_wString string_value;

    if (on_obj.GetUserString(w_key.c_str(), string_value)) {
        ON_String utf8_str = ON_String(string_value);
        return std::string(utf8_str.Array());
    } else {
        return std::string();
    }
}

bool RemoveUserString(ON_Object& on_obj, std::string& key) {
    std::wstring w_key = Utilities::utf8_to_wchar(key);

    return on_obj.SetUserString(w_key.c_str(), nullptr);
}

bool SetUserString(ON_Object& on_obj, std::string& key, std::string& value) {
    std::wstring w_key = Utilities::utf8_to_wchar(key);
    std::wstring w_val = Utilities::utf8_to_wchar(value);

    return on_obj.SetUserString(w_key.c_str(), w_val.c_str());
}

} // namespace ObjectUtilities
