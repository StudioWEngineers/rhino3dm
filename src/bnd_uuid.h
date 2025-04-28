#include "bindings.h"

#pragma once

typedef py::object BND_UUID;

BND_UUID ON_UUID_to_Binding(const ON_UUID& id);
ON_UUID Binding_to_ON_UUID(const BND_UUID& id);
