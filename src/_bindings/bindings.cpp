#include "bindings.h"
#include "layer_bindings.h"
#include "on_layer_bindings.h"
#include "layer_view_bindings.h"
#include "model_bindings.h"
#include "layer_table_bindings.h"
#include "point_bindings.h"

NB_MODULE(_rhino3dm, m) {
    m.doc() = "OpenNURBS wrapper.";

    ON::Begin();
    LayerBindings(m);
    ONLayerBindings(m);
    LayerViewBindings(m);
    LayerTableBindings(m);
    ModelBindings(m);
    PointBindings(m);
}
