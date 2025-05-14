#include "bindings.h"
#include "layer_bindings.h"
#include "layer_view_bindings.h"
#include "model_bindings.h"
#include "layer_table_bindings.h"

NB_MODULE(_rhino3dm, m) {
    m.doc() = "OpenNURBS wrapper.";

    ON::Begin();
    LayerBindings(m);
    LayerViewBindings(m);
    LayerTableBindings(m);
    ModelBindings(m);
}
