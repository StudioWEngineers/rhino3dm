#include "bindings.h"
#include "layer_bindings.h"
#include "layer_view_bindings.h"
#include "model_bindings.h"
#include "layer_table_bindings.h"

//const std::string version = ON::VersionQuartetAsString();

RH3DM_PYTHON_BINDING(_rhino3dm, m) {
    m.doc() = "rhino3dm python package. OpenNURBS wrappers with a RhinoCommon style";

    ON::Begin();
    LayerBindings(m);
    initLayerViewBindings(m);
    initLayerTableBindings(m);
    ModelBindings(m);
}
