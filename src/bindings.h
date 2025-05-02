#pragma once

// no need to export RH_C_FUNCTION in these libraries
#define RH_C_FUNCTION

#define ON_PYTHON_COMPILE
#if defined(NANOBIND)
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

#else
  #include <pybind11/pybind11.h>
  #include <pybind11/stl.h>
  #include <pybind11/operators.h>
  namespace py = pybind11;
  #define RH3DM_PYTHON_BINDING(name, variable) PYBIND11_MODULE(name, variable)
  typedef pybind11::module rh3dmpymodule;
#endif

//std::string ToStdString(const py::str& str);
//  #include "datetime.h"
//  #pragma comment(lib, "rpcrt4.lib")
  #pragma comment(lib, "shlwapi.lib")

#include "../lib/opennurbs/opennurbs.h"

typedef py::dict BND_DICT;
typedef py::tuple BND_Color;
typedef py::tuple BND_Color4f;
typedef py::tuple BND_TUPLE;
typedef py::handle BND_DateTime;
typedef py::list BND_LIST;

//BND_TUPLE CreateTuple(int count);
//BND_TUPLE NullTuple();
//template<typename T>
//void SetTuple(BND_TUPLE& tuple, int index, const T& value)
//{
//#if defined(NANOBIND)
//  UNIMPLEMENTED_EXCEPTION;
//#else
//  tuple[index] = value;
//#endif
//}

//buffer_info for nanobind
//#if defined(ON_PYTHON_COMPILE) && defined(NANOBIND)
//
//struct buffer_info {
//  std::string format;
//  std::vector<std::size_t> shape;
//  std::vector<std::size_t> strides;
//
//  buffer_info(
//      std::string format,
//      std::vector<std::size_t> shape_in,
//      std::vector<std::size_t> strides_in)
//      : format(std::move(format)),
//        shape(std::move(shape_in)),
//        strides(std::move(strides_in)) {}
//
//  buffer_info(const buffer_info&) = delete;
//  buffer_info& operator=(const buffer_info&) = delete;
//
//  buffer_info(buffer_info&& other) noexcept {
//    (*this) = std::move(other);
//  }
//
//  buffer_info& operator=(buffer_info&& rhs) noexcept {
//    format = std::move(rhs.format);
//    shape = std::move(rhs.shape);
//    strides = std::move(rhs.strides);
//    return *this;
//  }
//};
//
//
//#endif

//BND_LIST CreateList(int count);
//BND_LIST NullList();
//template<typename T>
//void Insert(BND_LIST& list, int index, const T& value)
//{
//  list.insert(index, value);
//}
//
//template<typename T>
//void Append(BND_LIST& list, const T& value)
//{
//  list.append(value);
//}

//BND_DateTime CreateDateTime(struct tm t);

//#include "bnd_color.h"
#include "bnd_uuid.h"
//#include "layer_view.h"
//#include "bnd_layer_table.h"
#include "layer.h"
//#include "model.h"
