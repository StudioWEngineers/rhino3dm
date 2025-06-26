#include "bindings.h"
#include "geometry_bindings.h"
#include "layer_bindings.h"
#include "layer_table_bindings.h"
#include "line_bindings.h"
#include "model_bindings.h"
#include "object_bindings.h"
#include "object_table_bindings.h"
#include "point_geometry_bindings.h"
#include "point3d_bindings.h"
#include "text_log_bindings.h"


NB_MODULE(_rhino3dm, m) {
    m.doc() = "OpenNURBS wrapper.";

    ON::Begin();
    ObjectBindings(m);

    Point3dBindings(m);

    GeometryBindings(m);
    LayerBindings(m);
    LayerTableBindings(m);
    LineBindings(m);
    ModelBindings(m);
    ObjectTableBindings(m);
    PointGeometryBindings(m);
    TextLogBindings(m);
}
