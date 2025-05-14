#include "bindings.h"
#include "layer_bindings.h"
#include "layer_view_bindings.h"
#include "model_bindings.h"
#include "layer_table_bindings.h"

NB_MODULE(_rhino3dm, m) {
    m.doc() = "rhino3dm python package. OpenNURBS wrappers with a RhinoCommon style";

    ON::Begin();
    LayerBindings(m);
    LayerViewBindings(m);
    LayerTableBindings(m);
    ModelBindings(m);
}
