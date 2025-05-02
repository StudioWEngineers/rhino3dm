#include "bindings.h"

//const std::string version = ON::VersionQuartetAsString();

RH3DM_PYTHON_BINDING(_rhino3dm, m) {
  m.doc() = "rhino3dm python package. OpenNURBS wrappers with a RhinoCommon style";
  //m.attr("Version") = py::cast(version);

  ON::Begin();
  LayerBindings(m);
  //ModelBindings(m);
  //initLayerViewBindings(m);
  //initLayerTableBindings(m);
  }

//std::string ToStdString(const py::str& str)
//{
//  std::string rc = py::cast<std::string>(str);
//  return rc;
//}
//
//BND_TUPLE CreateTuple(int count)
//{
//#if defined(NANOBIND)
//  BND_TUPLE rc = py::tuple();
//#else
//  BND_TUPLE rc = py::tuple(count);
//#endif
//  return rc;
//}
//
//BND_TUPLE NullTuple()
//{
//#if defined(NANOBIND)
//  return py::tuple();
//#else
//  return py::none();
//#endif
//}
//
//BND_LIST CreateList()
//{
//  BND_LIST rc = py::list();
//  return rc;
//}
//
//BND_LIST NullList()
//{
//#if defined(NANOBIND)
//  return py::list();
//#else
//  return py::none();
//#endif
//}

//BND_DateTime CreateDateTime(struct tm t)
//{
//  if (!PyDateTimeAPI) {
//    PyDateTime_IMPORT;
//  }
//  return PyDateTime_FromDateAndTime(t.tm_year + 1900,
//                                    t.tm_mon + 1,
//                                    t.tm_mday,
//                                    t.tm_hour,
//                                    t.tm_min,
//                                    t.tm_sec,
//                                    0);
//}
