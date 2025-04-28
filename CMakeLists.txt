cmake_minimum_required(VERSION 3.30)
project(rhino3dm)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message("Python Compile")
if(PYTHON_BINDING_LIB STREQUAL "NANOBIND")
  message("Using nanobind")
  add_compile_definitions( NANOBIND )
  set(DEV_MODULE Development.Module)
  find_package(Python 3.8 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

  if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
  endif()

  add_subdirectory(lib/nanobind)
else()
  message("Using pybind11")
  add_subdirectory(lib/pybind11)
endif()

include_directories(${PROJECT_NAME} PUBLIC lib/draco/src ${CMAKE_BINARY_DIR})

file(GLOB bindings_SRC "src/*.h" "src/*.cpp")

file(GLOB zlib_SRC "lib/opennurbs/zlib/*.h" "lib/opennurbs/zlib/*.c")

file(GLOB opennurbs_SRC "lib/opennurbs/*.h" "lib/opennurbs/*.cpp")
list(REMOVE_ITEM opennurbs_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/opennurbs/opennurbs_gl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/opennurbs/opennurbs_precompiledheader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/opennurbs/opennurbs_unicode_cp932.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/opennurbs/opennurbs_unicode_cp949.cpp"
)

# Compiler flags / definitions
add_definitions(
  -D_GNU_SOURCE
  -DON_COMPILING_OPENNURBS
  -DOPENNURBS_FREETYPE_INC_
  -DMY_ZCALLOC
  -DZ_PREFIX
  -DOPENNURBS_ZLIB_LIB_DIR
  -DUNICODE
  -DON_INCLUDE_DRACO
)

add_library(zlib_static STATIC ${zlib_SRC})
add_library(opennurbs_static STATIC ${opennurbs_SRC})
if(PYTHON_BINDING_LIB STREQUAL "NANOBIND")
  #need to build nanobind to link it?
  nanobind_build_library(nanobind)
  nanobind_add_module(_rhino3dm NB_STATIC ${bindings_SRC})
  target_link_libraries(_rhino3dm PRIVATE nanobind-static)
else()
  pybind11_add_module(_rhino3dm ${bindings_SRC})
  target_link_libraries(_rhino3dm PRIVATE pybind11::module)
endif()

target_link_libraries(_rhino3dm PRIVATE zlib_static)
target_link_libraries(_rhino3dm PRIVATE opennurbs_static)

add_subdirectory(lib/draco)
target_link_libraries(_rhino3dm PRIVATE draco::draco)

if(UNIX AND NOT APPLE)
  find_library(UUID_LIB uuid REQUIRED)
  target_link_libraries(_rhino3dm PRIVATE ${UUID_LIB})
endif()

install(FILES
    ${CMAKE_SOURCE_DIR}/src/__init__.py
    ${CMAKE_SOURCE_DIR}/src/__init__.pyi
    ${CMAKE_SOURCE_DIR}/src/py.typed
    DESTINATION rhino3dm
)

install(TARGETS _rhino3dm
    LIBRARY DESTINATION rhino3dm
    RUNTIME DESTINATION rhino3dm
    ARCHIVE DESTINATION rhino3dm)
