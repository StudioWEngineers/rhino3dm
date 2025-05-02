#include "bindings.h"

BND_Color ON_Color_to_Binding(const ON_Color& color) {
    return py::make_tuple(color.Red(), color.Green(), color.Blue(), 255 - color.Alpha());
}

ON_Color Binding_to_ON_Color(const BND_Color& color) {
    int r = py::cast<int>(color[0]);
    int g = py::cast<int>(color[1]);
    int b = py::cast<int>(color[2]);
    int a = py::cast<int>(color[3]);
    return ON_Color(r, g, b, 255-a);
}

//BND_Color4f ON_4fColor_to_Binding(const ON_4fColor& color)
//{
//  return py::make_tuple(color.Red(), color.Green(), color.Blue(), color.Alpha());
//}


//ON_4fColor Binding_to_ON_4fColor(const BND_Color4f& color)
//{
//  float r = py::cast<float>(color[0]);
//  float g = py::cast<float>(color[1]);
//  float b = py::cast<float>(color[2]);
//  float a = py::cast<float>(color[3]);
//  return ON_4fColor(r, g, b, a);
//}
