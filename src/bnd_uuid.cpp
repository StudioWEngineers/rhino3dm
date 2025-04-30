#include "bindings.h"

static py::object make_uuid;
BND_UUID ON_UUID_to_Binding(const ON_UUID& id)
{
  if (make_uuid.ptr() == nullptr)
  {
    rh3dmpymodule uuid_module = rh3dmpymodule::import("uuid");
    make_uuid = uuid_module.attr("UUID");
  }
  char s[37];
  memset(s, 0, sizeof(s));

  char* suuid = ON_UuidToString(id, s);
  py::object guid = make_uuid(suuid);
  return guid;
}

ON_UUID Binding_to_ON_UUID(const BND_UUID& id)
{
#if !defined(NANOBIND)
  std::string s = py::str(id);
#else
  std::string s = py::cast<std::string>(id.attr("hex"));
#endif
  return ON_UuidFromString(s.c_str());
}
