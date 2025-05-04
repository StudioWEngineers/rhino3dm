#pragma once

// no need to export RH_C_FUNCTION in these libraries
//#define RH_C_FUNCTION

#define ON_PYTHON_COMPILE
//#if defined(NANOBIND)
  #include <nanobind/nanobind.h>
  #include <nanobind/stl/string.h>
  #include <nanobind/stl/wstring.h>
  #include <nanobind/stl/tuple.h>
  #include <nanobind/operators.h>
  #include <nanobind/stl/vector.h>
  #include <vector>
  #include <tuple>
  namespace py = nanobind;
  typedef nanobind::module_ rh3dmpymodule;
#define RH3DM_PYTHON_BINDING(name, variable) NB_MODULE(name, variable)
#define def_property def_prop_rw
#define def_property_readonly def_prop_ro
#define def_readonly def_ro
#define def_readwrite def_rw
#define def_property_readonly_static def_prop_ro_static
#define import import_
#define UNIMPLEMENTED_EXCEPTION throw std::exception()

//#else
  //#include <pybind11/pybind11.h>
  //#include <pybind11/stl.h>
  //#include <pybind11/operators.h>
  //namespace py = pybind11;
  //#define RH3DM_PYTHON_BINDING(name, variable) PYBIND11_MODULE(name, variable)
  //typedef pybind11::module rh3dmpymodule;
//#endif

//#pragma comment(lib, "shlwapi.lib")

#include "../opennurbs_includes.h"

//typedef py::dict BND_DICT;
//typedef py::tuple BND_Color;
//typedef py::tuple BND_Color4f;
//typedef py::tuple BND_TUPLE;
//typedef py::handle BND_DateTime;
//typedef py::list BND_LIST;
//typedef py::object BND_UUID;  // or py::handle

//#include "layer.h"
