#include <codecvt>
#include <locale>
#include <sstream>

#include "layer_utilities.h"


namespace LayerUtilities {

std::string GetName(const ON_Layer& layer) {
    ON_String utf_8_str(layer.Name());
    const char* utf_8 = utf_8_str.Array();
    return utf_8 ? std::string(utf_8) : std::string();
}

std::string GetPathSeparator() {
    ON_String utf_8_str(ON_ModelComponent::NamePathSeparator);
    const char* utf_8 = utf_8_str.Array();
    return utf_8 ? std::string(utf_8) : std::string();
}

void SetName(ON_Layer& layer, const std::string& name) {
    ON_wString w_name(name.c_str());
    layer.SetName(w_name);
}

std::string ToString(const ON_Layer& layer) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::string name_str = convert.to_bytes(layer.NameAsPointer());

    char p_uuid_str[37];
    char uuid_str[37];
    ON_UuidToString(layer.ParentId(), p_uuid_str);
    ON_UuidToString(layer.Id(), uuid_str);

    ON_Color color = layer.Color();
    std::ostringstream color_stream;
    color_stream << "(" << color.Red() << ", " << color.Green() << ", " << color.Blue() << ", " << 255 - color.Alpha() << ")";

    ON_Color p_color = layer.PlotColor();
    std::ostringstream p_color_stream;
    p_color_stream << "(" << p_color.Red() << ", " << p_color.Green() << ", " << p_color.Blue() << ", " << 255 - p_color.Alpha() << ")";

    std::ostringstream output;
    output << "Layer with properties:\n"
           << "\tcolor = " << color_stream.str() << "\n"
           << "\tiges_level = " << layer.IgesLevel() << "\n"
           << "\tindex = " << layer.Index() << "\n"
           << "\tis_expanded = " << std::boolalpha << layer.m_bExpanded << "\n"
           << "\tis_locked = " << layer.IsLocked() << "\n"
           << "\tis_visible = " << layer.IsVisible() << "\n"
           << "\tlayer_uuid = " << std::string(uuid_str) << "\n"
           << "\tline_type_index = " << layer.LinetypeIndex() << "\n"
           << "\tname = '" << name_str << "'\n"
           << "\tparent_uuid = " << std::string(p_uuid_str) << "\n"
           << "\tpath separator = " << LayerUtilities::GetPathSeparator() << "\n"
           << "\tpersistent_locking = " << layer.PersistentLocking() << "\n"
           << "\tpersistent_visibility = " << layer.PersistentVisibility() << "\n"
           << "\tplot_color = " << p_color_stream.str() << "\n"
           << "\tplot_weight = " << layer.PlotWeight() << "\n"
           << "\trender_material_index = " << layer.RenderMaterialIndex() << "\n";
    return output.str();
}

} // namespace LayerUtilities
