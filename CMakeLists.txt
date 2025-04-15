cmake_minimum_required(VERSION 3.18)
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

# Add draco add_library
include_directories(${PROJECT_NAME} PUBLIC lib/draco/src ${CMAKE_BINARY_DIR})

file(GLOB bindings_SRC "src/*.h" "src/*.cpp")
file(GLOB zlib_SRC "lib/opennurbs/zlib/*.h" "lib/opennurbs/zlib/*.c")

# temporarily rename the 4 cpp files that we don't want to compile on OSX
file(RENAME "lib/opennurbs/opennurbs_gl.cpp" "lib/opennurbs/opennurbs_gl.skip")
file(RENAME "lib/opennurbs/opennurbs_unicode_cp932.cpp" "lib/opennurbs/opennurbs_unicode_cp932.skip")
file(RENAME "lib/opennurbs/opennurbs_unicode_cp949.cpp" "lib/opennurbs/opennurbs_unicode_cp949.skip")
file(RENAME "lib/opennurbs/opennurbs_precompiledheader.cpp" "lib/opennurbs/opennurbs_precompiledheader.skip")
file(GLOB opennurbs_SRC "lib/opennurbs/*.h" "lib/opennurbs/*.cpp")
file(RENAME "lib/opennurbs/opennurbs_gl.skip" "lib/opennurbs/opennurbs_gl.cpp")
file(RENAME "lib/opennurbs/opennurbs_unicode_cp932.skip" "lib/opennurbs/opennurbs_unicode_cp932.cpp")
file(RENAME "lib/opennurbs/opennurbs_unicode_cp949.skip" "lib/opennurbs/opennurbs_unicode_cp949.cpp")
file(RENAME "lib/opennurbs/opennurbs_precompiledheader.skip" "lib/opennurbs/opennurbs_precompiledheader.cpp")

add_definitions(-D_GNU_SOURCE)
add_definitions(-DON_COMPILING_OPENNURBS)
add_definitions(-DOPENNURBS_FREETYPE_INC_)
add_definitions(-DMY_ZCALLOC -DZ_PREFIX)
add_definitions(-DOPENNURBS_ZLIB_LIB_DIR)
add_definitions(-DUNICODE)
add_definitions(-DON_INCLUDE_DRACO)

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

install(TARGETS _rhino3dm
        LIBRARY DESTINATION rhino3dm
        RUNTIME DESTINATION rhino3dm
        ARCHIVE DESTINATION rhino3dm)
